#include "WardAudio.h"
#include "WardGame.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "EngineUtils.h"

TArray<UAudioComponent*> AWardAudioDirector::MusicComponents() const
{return {ExplorationLayer,AlertLayer,CombatLayer,RageLayer,BossLayer,ExtractionLayer,CalmLayer,MysteryLayer};}
TArray<float> AWardAudioDirector::GetMusicGains() const
{TArray<float> Result;for(auto* C:MusicComponents())Result.Add(C->VolumeMultiplier);return Result;}
void AWardAudioDirector::LoadScore()
{
    TObjectPtr<USoundBase>* Assets[]={&Exploration,&Alert,&Combat,&Rage,&Boss,&Extraction,&Calm,&Mystery};
    const TCHAR* IDs[]={TEXT("exploration"),TEXT("alert"),TEXT("combat"),TEXT("rage"),TEXT("boss"),TEXT("extraction"),TEXT("calm"),TEXT("mystery")};
    auto ScoreLayers=MusicComponents();
    for(int32 I=0;I<8;++I)
    {
        const FString Path=FString(TEXT("/Game/Ward09/Audio/ScoreV16/M_"))+IDs[I];
        if(auto* S=LoadObject<USoundBase>(nullptr,*Path)){*Assets[I]=S;++LoadedScoreClips;}
        ScoreLayers[I]->Stop();ScoreLayers[I]->SetSound(*Assets[I]);ScoreLayers[I]->SetVolumeMultiplier(0);
    }
}
void AWardAudioDirector::TickScore(float Delta,AWardPlayer* Player,AWardDirector* Story)
{
    const int32 Step=Story?Story->Step:0;const bool Complete=Story&&Story->Completed;
    const bool Alive=Player->IsAlive();const bool StepChanged=Step!=ScoreLastStep;
    if(StepChanged){ScoreLastStep=Step;QuietTime=0;ScoreSampleTime=0;}
    // Perception at 5 Hz. Walls and other floors cannot start combat music by proximity alone.
    ScoreSampleTime-=Delta;
    if(ScoreSampleTime<=0)
    {
        ScoreSampleTime=.2f;ScoreDanger=ScoreNearby=ScoreBoss=ScoreRage=false;
        for(TActorIterator<AWardEnemy> It(GetWorld());It;++It)
        {
            if(!It->Active||!It->IsAlive())continue;
            const FVector Target=It->GetHitRegionCenter(TEXT("head")),Eye=Player->GetPawnViewLocation();
            const float Distance=FVector::Dist2D(Target,Eye);if(Distance>1800||FMath::Abs(Target.Z-Eye.Z)>250)continue;
            FCollisionQueryParams Q(SCENE_QUERY_STAT(WardScoreSight),true,Player);FHitResult Hit;
            const bool Clear=!GetWorld()->LineTraceSingleByChannel(Hit,Eye,Target,ECC_Visibility,Q)||Hit.GetActor()==*It;
            if(!Clear)continue;
            ScoreNearby=true;
            const bool Attack=It->State==EWardEnemyState::Windup||It->State==EWardEnemyState::Recover;
            if(Distance<1000||Attack){ScoreDanger=true;ScoreBoss|=It->Species==EWardSpecies::Warden;ScoreRage|=It->RageStage>0;}
        }
    }
    DangerHold=ScoreDanger?6.f:FMath::Max(0.f,DangerHold-Delta);
    AlertHold=ScoreNearby?3.f:FMath::Max(0.f,AlertHold-Delta);
    QuietTime=ScoreNearby||DangerHold>0?0:QuietTime+Delta;
    const bool Investigation=Step==1||Step==4||Step==6||Step==7||Step==8;
    FString Wanted=!Alive?TEXT("death"):Complete?TEXT("extraction"):ScoreBoss?TEXT("boss"):ScoreRage?TEXT("rage"):DangerHold>0?TEXT("combat"):AlertHold>0?TEXT("alert"):
        Step>=12&&Step<14?TEXT("alert"):Investigation?TEXT("mystery"):QuietTime>14?TEXT("calm"):TEXT("exploration");
    // Hold an established combat tier until its real danger tail ends; no one-frame musical flapping.
    if(Alive&&!Complete&&!ScoreDanger&&DangerHold>0&&(MixState==TEXT("boss")||MixState==TEXT("rage")))Wanted=MixState;
    const bool Urgent=!Alive||Complete||ScoreDanger;
    ScoreStateAge+=Delta;
    if(ScoreIndex<0||Wanted!=MixState&&(Urgent||StepChanged||ScoreStateAge>=4))
    {
        MixState=Wanted;ScoreStateAge=0;
        ScoreIndex=Wanted==TEXT("alert")?1:Wanted==TEXT("combat")?2:Wanted==TEXT("rage")?3:Wanted==TEXT("boss")?4:Wanted==TEXT("extraction")?5:Wanted==TEXT("calm")||Wanted==TEXT("death")?6:Wanted==TEXT("mystery")?7:0;
        for(int32 I=0;I<8;++I)ScoreFrom[I]=ScoreWeights[I];ScoreFade=0;
        ScoreFadeSeconds=!Alive?2.f:ScoreDanger?1.25f:Complete?3.f:4.f;
        UE_LOG(LogTemp,Display,TEXT("WARD_SCORE state=%s step=%d"),*MixState,Step);
    }
    const bool Speaking=DialogueEnabled&&EffectsVolume>0&&Story&&Story->RadioVoice&&Story->RadioVoice->IsPlaying();
    MusicDucking=FMath::FInterpTo(MusicDucking,Speaking?.42f:1.f,Delta,Speaking?7.f:1.5f);
    ScoreFade=FMath::Min(1.f,ScoreFade+Delta/ScoreFadeSeconds);
    const float Smooth=ScoreFade*ScoreFade*(3-2*ScoreFade);
    auto ScoreLayers=MusicComponents();const float Base=Muted?0:MusicVolume*MusicDucking*(Alive?1.f:.18f);
    for(int32 I=0;I<8;++I)
    {
        ScoreWeights[I]=FMath::Lerp(ScoreFrom[I],I==ScoreIndex?1.f:0.f,Smooth);
        auto* Layer=ScoreLayers[I];const float Gain=ScoreWeights[I]*Base;
        if(Gain>.0001f&&Layer->Sound)
        {
            Layer->SetVolumeMultiplier(Gain);
            // Start on demand; never rely on silent layers surviving Unreal voice virtualization.
            if(!Layer->IsPlaying())Layer->Play(ScorePositions[I]);
            ScorePositions[I]=FMath::Fmod(ScorePositions[I]+Delta,FMath::Max(1.f,Layer->Sound->GetDuration()));
        }
        else {Layer->SetVolumeMultiplier(0);if(Layer->IsPlaying())Layer->Stop();}
    }
}

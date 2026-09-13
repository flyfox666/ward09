#include "WardLanguage.h"
#include "WardGame.h"
#include "Engine/Canvas.h"
#include "Internationalization/Regex.h"

namespace WardLanguage
{
    static bool English=false;
    bool IsEnglish(){return English;}
    void SetEnglish(bool Value){English=Value;}
    struct FTranslation{FString Source,Target;};
    static const TArray<FTranslation> Catalog={
#include "WardEnglishCatalog.inl"
    };
    static FString Translate(const FString& Source);
    FString Text(const FString& Source)
    {
        if(!English)return Source;
        bool HasHan=false;for(TCHAR C:Source)if(C>=0x3400&&C<=0x9fff){HasHan=true;break;}
        if(!HasHan)return Source;
        static TMap<FString,FString> Cache;
        if(const auto* Found=Cache.Find(Source))return *Found;
        const FString Result=Translate(Source);if(Cache.Num()>4096)Cache.Reset();Cache.Add(Source,Result);return Result;
    }
    static FString Translate(const FString& Source)
    {
        for(const auto& Row:Catalog)if(Source==Row.Source)return Row.Target;
        // Format-bearing strings keep their numbers and optional interaction suffixes.
        const FRegexPattern Format(TEXT("%[-+0-9.]*[dfs]"));
        for(const auto& Row:Catalog)
        {
            if(!Row.Source.Contains(TEXT("%")))continue;
            FRegexMatcher Tokens(Format,Row.Source);FString Pattern=TEXT("^");int32 Previous=0,Count=0;
            while(Tokens.FindNext())
            {
                FString Literal=Row.Source.Mid(Previous,Tokens.GetMatchBeginning()-Previous);
                for(TCHAR C:Literal){if(FString(TEXT("\\.^$|()[]{}*+?")).Contains(FString::Chr(C)))Pattern+=TEXT("\\");Pattern.AppendChar(C);}
                Pattern+=Tokens.GetCaptureGroup(0).EndsWith(TEXT("s"))?TEXT("(.*)"):TEXT("([0-9.+-]+)");
                Previous=Tokens.GetMatchEnding();++Count;
            }
            if(!Count)continue;
            for(TCHAR C:Row.Source.Mid(Previous)){if(FString(TEXT("\\.^$|()[]{}*+?")).Contains(FString::Chr(C)))Pattern+=TEXT("\\");Pattern.AppendChar(C);}
            Pattern+=TEXT("$");FRegexMatcher Match(FRegexPattern(Pattern),Source);
            if(!Match.FindNext())continue;
            FRegexMatcher OutputTokens(Format,Row.Target);FString Result;Previous=0;int32 Index=1;
            while(OutputTokens.FindNext()){Result+=Row.Target.Mid(Previous,OutputTokens.GetMatchBeginning()-Previous)+Text(Match.GetCaptureGroup(Index++));Previous=OutputTokens.GetMatchEnding();}
            return Result+Row.Target.Mid(Previous);
        }
        // Composed labels (weapon + ammo, pickup + hint) retain canonical Chinese state.
        FString Result=Source;
        for(const auto& Row:Catalog)if(!Row.Source.Contains(TEXT("%"))&&Row.Source.Len()>1)Result=Result.Replace(*Row.Source,*Row.Target,ESearchCase::CaseSensitive);
        return Result;
    }
    TArray<FString> Wrap(UCanvas* Canvas,UFont* Font,const FString& Source,float Width,float Scale)
    {
        const FString Value=Text(Source);TArray<FString> Lines;FString Line;
        for(int32 I=0;I<Value.Len();++I)
        {
            if(Value[I]=='\n'){Lines.Add(Line);Line.Empty();continue;}
            Line.AppendChar(Value[I]);float W=0,H=0;Canvas->StrLen(Font,Line,W,H);
            if(W*Scale<=Width||Line.Len()<2)continue;
            int32 Split=Line.Len()-1;
            if(English){int32 Space;if(Line.FindLastChar(' ',Space)&&Space>0)Split=Space;}
            Lines.Add(Line.Left(Split).TrimEnd());Line=Line.Mid(Split).TrimStart();
        }
        if(!Line.IsEmpty())Lines.Add(Line);return Lines;
    }
}
void AWardHUD::DrawText(const FString& Source,FLinearColor Color,float X,float Y,UFont* Font,float Scale,bool ScalePosition)
{
    const FString Value=WardLanguage::Text(Source);
    // Keep labels in the viewport; panel-specific fitting happens before this call.
    if(Canvas&&!ScalePosition){float W=0,H=0;Canvas->StrLen(Font,Value,W,H);if(W>0)Scale=FMath::Min(Scale,FMath::Max(1.f,Canvas->SizeX-X-24)/W);}
    Super::DrawText(Value,Color,X,Y,Font,Scale,ScalePosition);
}

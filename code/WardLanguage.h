#pragma once
#include "CoreMinimal.h"
class UCanvas;
class UFont;
namespace WardLanguage
{
    bool IsEnglish();
    void SetEnglish(bool Value);
    FString Text(const FString& Source);
    TArray<FString> Wrap(UCanvas* Canvas,UFont* Font,const FString& Source,float Width,float Scale);
}

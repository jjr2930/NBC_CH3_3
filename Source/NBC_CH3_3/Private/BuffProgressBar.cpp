#include "BuffProgressBar.h"
#include "JUtility.h"
#include "Buff.h"

#include <Components/ProgressBar.h>
#include <Engine/Texture2D.h>
#include <Components/Image.h>

void UBuffProgressBar::BindBuff(FDurationBuff* Buff)
{
    DurationBuff = Buff;

    SetTexture(DurationBuff->GetIconTexture());
}

bool UBuffProgressBar::IsMyBuff(FDurationBuff* Buff)
{
    if (nullptr == Buff)
        return false;

    return DurationBuff == Buff;
}

void UBuffProgressBar::SetPercent(float Percent)
{
    RemainTimeProgressBar->SetPercent(Percent);
}

void UBuffProgressBar::SetTexture(UTexture2D* IconTexture)
{
    Icon->SetBrushFromTexture(IconTexture);
}

void UBuffProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    JASSERT(nullptr != DurationBuff, "Duration Buff is nullptr");

    float BuffStartTime = DurationBuff->GetStartTime();
    float BuffDuration = DurationBuff->GetDuration();

    float Now = (float)(GetWorld()->TimeSeconds);
    float DuringTime = Now - BuffStartTime;
    float Percent = DuringTime / BuffDuration;
    Percent = 1.0f - Percent;

    RemainTimeProgressBar->SetPercent(Percent);
}

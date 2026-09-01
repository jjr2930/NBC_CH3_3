#include "IngameWidget.h"
#include "IngameState.h"
#include "JUtility.h"

#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UIngameWidget::SetWaveDuration(float InRemainTime)
{
    int remainSeconds = (int)InRemainTime;

    TimeText->SetText(FText::AsNumber(remainSeconds));
}


void UIngameWidget::SetPoint(int InCurrentPoint, int InTargetPoint)
{
    FText TextToDisplay = FText::Format(
        FText::FromString(TEXT("{0}/{1}"))
        , InCurrentPoint
        , InTargetPoint
    );

    JASSERT(!FMath::IsNearlyZero((float(InTargetPoint))), "Can not divide zero!");

    CoinText->SetText(TextToDisplay);
    CoinProgressbar->SetPercent((float)InCurrentPoint / (float)InTargetPoint);
}
void UIngameWidget::SetWaveText(int InCurrentWaveIndex, int InTotalWaveCount)
{
    FText TextToDisplay = FText::Format(
        FText::FromString(TEXT("{0}/{1}"))
        , InCurrentWaveIndex + 1    //인덱스는 0부터 시작한다.
        , InTotalWaveCount
    );

    WaveText->SetText(TextToDisplay);
}

void UIngameWidget::NativeOnInitialized()
{
    AIngameState* IngameState = Cast<AIngameState>(GetWorld()->GetGameState());
    checkf(IsValid(IngameState), TEXT("Current game stat is not IngameState type"));

    IngameState->OnCoinCountChanged.AddUObject(this, &UIngameWidget::SetPoint);
    IngameState->OnRemainTimeChanged.AddUObject(this, &UIngameWidget::SetWaveDuration);
    IngameState->OnWaveIndexChanged.AddUObject(this, &UIngameWidget::SetWaveText);

    //처음엔 얻어와서 세팅하자.
    int CurrentPickupCount = IngameState->GetCurrentCoinCount();
    int TargetCoinCount = IngameState->GetTargetCoinCount();
    int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
    int TotalWaveCount = IngameState->GetTotalWaveCount();

    SetPoint(CurrentPickupCount, TargetCoinCount);
    SetWaveText(CurrentWaveIndex, TotalWaveCount);
}
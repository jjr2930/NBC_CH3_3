#include "IngameWidget.h"
#include "IngameState.h"
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UIngameWidget::SetWaveDuration(float InRemainTime)
{
    int remainSeconds = (int)InRemainTime;

    TimeText->SetText(FText::AsNumber(remainSeconds));
}


void UIngameWidget::SetPickupCount(int InPickupCount, int InTargetItemCount)
{
    FText TextToDisplay = FText::Format(
        FText::FromString(TEXT("{0}/{1}"))
        , InPickupCount
        , InTargetItemCount
    );

    PickupCount->SetText(TextToDisplay);
    PickupCountProgressbar->SetPercent((float)InPickupCount / (float)InTargetItemCount);
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

    IngameState->OnPickupCountChanged.AddUObject(this, &UIngameWidget::SetPickupCount);
    IngameState->OnRemainTimeChanged.AddUObject(this, &UIngameWidget::SetWaveDuration);
    IngameState->OnWaveIndexChanged.AddUObject(this, &UIngameWidget::SetWaveText);

    //처음엔 얻어와서 세팅하자.
    int CurrentPickupCount = IngameState->GetCurrentPickUpCount();
    int TargetPoint = IngameState->GetTotalPickUpCount();
    int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
    int TotalWaveCount = IngameState->GetTotalWaveCount();

    SetPickupCount(CurrentPickupCount, TargetPoint);
    SetWaveText(CurrentWaveIndex, TotalWaveCount);
}
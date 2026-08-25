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

    this->PickupCount->SetText(TextToDisplay);
    this->PickupCountProgressbar->SetPercent((float)InPickupCount / (float)InTargetItemCount);
}

void UIngameWidget::NativeOnInitialized()
{
    AIngameState* IngameState = Cast<AIngameState>(GetWorld()->GetGameState());
    checkf(IsValid(IngameState), TEXT("Current game stat is not IngameState type"));

    IngameState->OnPickupCountChanged.AddUObject(this, &UIngameWidget::SetPickupCount);
    IngameState->OnRemainTimeChanged.AddUObject(this, &UIngameWidget::SetWaveDuration);

    //처음엔 얻어와서 세팅하자.
    int CurrentPickupCount = IngameState->GetCurrentPickUpCount();
    int TotalPickupCount = IngameState->GetTotalPickUpCount();

    SetPickupCount(CurrentPickupCount, TotalPickupCount);
}
#include "GatchaWidget.h"
#include "JUtility.h"
#include "FieldItemSpawnRow.h"

#include <Components/Image.h>
#include <Animation/WidgetAnimation.h>

void UGatchaWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    checkf(IsValid(GatchaAnimation), TEXT("GatchaAnimation is not setted"));

    FWidgetAnimationDynamicEvent FinishedEvent;
    FinishedEvent.BindDynamic(
        this,
        &UGatchaWidget::HandleAnimationFinshed
    );

    BindToAnimationFinished(GatchaAnimation, FinishedEvent);
}

void UGatchaWidget::HandleAnimationFinshed()
{
    AnimationFinishedCallback.Execute();
}

void UGatchaWidget::PlayAnimation(FGatchaAnimationFinishedEvent Callback)
{
    AnimationFinishedCallback = Callback;
    
    Super::PlayAnimation(GatchaAnimation);
}

void UGatchaWidget::SetIcon(TObjectPtr<UTexture2D> InTexture)
{    
    ItemIcon->SetBrushFromTexture(InTexture);
}
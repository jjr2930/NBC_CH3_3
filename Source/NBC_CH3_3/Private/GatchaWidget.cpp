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

void UGatchaWidget::SetItemType(EItemType ItemType)
{
    JASSERT(Textures.Contains(ItemType)
        , "Texture is not exist, ItemType:%s"
        , *StaticEnum<EItemType>()->GetNameStringByValue((uint64)ItemType));

    JASSERT(IsValid(Textures[ItemType])
        , "Key(%s) exist but texture is not exist"
        , *StaticEnum<EItemType>()->GetNameStringByValue((uint64)ItemType));

    ItemIcon->SetBrushFromTexture(Textures[ItemType]);
}
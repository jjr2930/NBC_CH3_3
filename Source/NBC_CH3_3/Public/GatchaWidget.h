#pragma once

#include <Blueprint/UserWidget.h>
#include "CoreMinimal.h"
#include <Delegates/DelegateCombinations.h>
#include "Enums.h"
#include "GatchaWidget.generated.h"

class UDataTable;
class UImage;
class UTexture2D;

UCLASS()
class NBC_CH3_3_API UGatchaWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE(FGatchaAnimationFinishedEvent);

public:
    virtual void NativeOnInitialized() override;
    void PlayAnimation(FGatchaAnimationFinishedEvent Callback);
    void SetItemType(EItemType ItemType);

protected:
    UFUNCTION()
    void HandleAnimationFinshed();

    //member fields
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gatcha|Properties")
    TObjectPtr<UDataTable> ItemDropTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gatcha|Properties")
    TMap<EItemType, TObjectPtr<UTexture2D>> Textures;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ItemIcon;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> GatchaAnimation;

    FGatchaAnimationFinishedEvent AnimationFinishedCallback;
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FailedWidget.generated.h"

class UButton; 
class UWorld;

UCLASS()
class NBC_CH3_3_API UFailedWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void OnClicked();

protected:
    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UButton> Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FailedWidget|Properties")
    TSoftObjectPtr<UWorld> MenuLevel;
};

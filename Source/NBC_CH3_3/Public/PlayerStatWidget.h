// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatComponent.h"
#include "PlayerStatWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UStatComponent;

UCLASS()
class NBC_CH3_3_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetStatComponent(TObjectPtr<UStatComponent> InStatComponent);

    UFUNCTION()
    void OnStatChanged(ECharacterStatType InStatType, int Value);

protected: 
    void RefreshHealthUi();
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> HealthProgressBar;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> HealthProgressBarText;

    TObjectPtr<UStatComponent> TargetStatComponent;
};

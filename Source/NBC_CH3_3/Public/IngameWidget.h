// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class NBC_CH3_3_API UIngameWidget : public UUserWidget
{
	GENERATED_BODY()	

public:
    void SetWaveDuration(float InRemainTime);
    void SetPickupCount(int InPickupItemCount, int InTargetItemCount);
    void SetWaveText(int InCurrentWaveIndex, int InTotalWaveCount);

protected:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TimeText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> PickupCountProgressbar;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PickupCount;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> WaveText;
};

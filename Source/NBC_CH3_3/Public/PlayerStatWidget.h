// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class NBC_CH3_3_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    TObjectPtr<UProgressBar> HealthProgressBar;
    TObjectPtr<UTextBlock> HealthProgressBarText;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "IngameState.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_3_API AIngameState : public AGameStateBase
{
	GENERATED_BODY()

public:
    void SetCurrentPickUpCount(int PickupCount);
    void SetTotalPickUpCount(int Count);
    int GetCurrentPickUpCount() const;
    int GetTotalPickUpCount() const;

protected:
    int CurrentPickUpCount;
    int TotalPickupCount;
};

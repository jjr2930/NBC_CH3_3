// Fill out your copyright notice in the Description page of Project Settings.
#include "IngameGameMode.h"
#include "JUtility.h"
#include "FieldItemBase.h"
#include "Kismet/GameplayStatics.h"

void AIngameGameMode::PickupFieldItem(const AFieldItemBase& Item)
{
    if (!IsValid(&Item))
    {
        JError("Argument is not field item");
        return;
    }

    CurrentPickupCount++;
    if (CurrentPickupCount >= TargetPickupCount)
    {
        //set next wawve
        JLog("%d Wave Finished", CurrentWave);
        if (CurrentWave >= TotalWaveCount)
        {
            JLog("Current stage cleared!, ready for next stage!");
            UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextStage);
        }
        else
        {
            CurrentWave++;
            JLog("%d Wave started", CurrentWave);
        }
    }
}

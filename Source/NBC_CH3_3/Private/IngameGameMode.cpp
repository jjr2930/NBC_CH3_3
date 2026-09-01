// Fill out your copyright notice in the Description page of Project Settings.
#include "IngameGameMode.h"
#include "JUtility.h"
#include "FieldItem.h"
#include "Kismet/GameplayStatics.h"
#include "IngameState.h"
#include "StatComponent.h"
#include "IngameGameInstance.h"
#include "InventoryComponent.h"
#include "Enums.h"
#include "FieldItemSpawnRow.h"

AIngameGameMode::AIngameGameMode()
    : IngameState(nullptr)
{
    GameStateClass = AIngameState::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
}


void AIngameGameMode::SetNextWave()
{
    int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
    IngameState->SetCurrentWaveIndex(++CurrentWaveIndex );
    JLog("%d 웨이브 시작!", CurrentWaveIndex + 1);

    IngameState->SetStartTime(GetWorld()->TimeSeconds);
    IngameState->SetCurrentCoinAmount(0);
}


void AIngameGameMode::OnItemAdded(const FInventoryItemData& AddedItem)
{
    if (AddedItem.ItemType == EItemType::QuestItem)
    {
        IngameState->SetCurrentCoinAmount(AddedItem.StackCount);
        if (IngameState->GetCurrentCoinCount() >= IngameState->GetTargetCoinCount())
        {
            int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
            JLog("%d 웨이브 완료", CurrentWaveIndex + 1);

            SetNextWave();
        }
    }
}

void AIngameGameMode::BeginPlay()
{
    IngameState = Cast<AIngameState>(GetWorld()->GetGameState());
    checkf(IsValid(IngameState), TEXT("Current game state is not IngameState"));

    IngameState->SetCurrentWaveIndex(-1);
    SetNextWave();
}

void AIngameGameMode::Tick(float DeltaTime)
{
    float StartTime = IngameState->GetStartTime();
    float NowTime = (float)GetWorld()->TimeSeconds;
    float WaveDuration = IngameState->GetWaveDuration();
    float RemainTime = WaveDuration - (NowTime - StartTime);

    IngameState->SetRemainTime(RemainTime);

    if (RemainTime <= 0.0f)
    {
        JLog("Time Over");

        checkf(!FailedLevel.IsNull(), TEXT("Failed level is invalid"));
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), FailedLevel);
    }
}

// Fill out your copyright notice in the Description page of Project Settings.
#include "IngameGameMode.h"
#include "JUtility.h"
#include "FieldItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "IngameState.h"

AIngameGameMode::AIngameGameMode()
{
    GameStateClass = AIngameState::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
}

void AIngameGameMode::PickupFieldItem(const AFieldItemBase& Item)
{
    checkf(IsValid(&Item), TEXT("Item is not valiud"));
    checkf(IsValid(IngameState), TEXT("Current game state is not IngameState"));

    JLog("아이템 습득") 
    int CurrentPickupCount = IngameState->GetCurrentPickUpCount();
    IngameState->SetCurrentPickUpCount(++CurrentPickupCount);

    int TotalPickupCount = IngameState->GetTotalPickUpCount();
    if (CurrentPickupCount < TotalPickupCount)
        return;
    
    int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
    JLog("%d Wave cleared", CurrentWaveIndex);

    int TotalWaveCount = IngameState->GetTotalWaveCount();
    if (CurrentWaveIndex == TotalWaveCount - 1) //인덱스는 0부터 시작하니까...
    {
        JLog("StageCleared, load next stage");
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextStage);
    }
    else
    {
        SetNextWave();
    }
}

void AIngameGameMode::SetNextWave()
{
    int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
    IngameState->SetCurrentWaveIndex(++CurrentWaveIndex );
    JLog("Good, you cleared this wave, ready for next wave");
    JLog("%d 웨이브 시작!", CurrentWaveIndex + 1);

    IngameState->SetStartTime(GetWorld()->TimeSeconds);
    IngameState->SetCurrentPickUpCount(0);
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

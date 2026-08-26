// Fill out your copyright notice in the Description page of Project Settings.
#include "IngameGameMode.h"
#include "JUtility.h"
#include "FieldItem.h"
#include "Kismet/GameplayStatics.h"
#include "IngameState.h"
#include "StatComponent.h"
#include "IngameGameInstance.h"

#include "FieldItemSpawnRow.h"

AIngameGameMode::AIngameGameMode()
    : IngameState(nullptr)
{
    GameStateClass = AIngameState::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
}

void AIngameGameMode::PickupFieldItem(const AFieldItem& Item, AActor* Who)
{
    checkf(IsValid(&Item), TEXT("Item is not valiud"));
    checkf(IsValid(IngameState), TEXT("Current game state is not IngameState"));

    FFieldItemSpawnRow* Row = Item.Roll();
    int Amount = Row->RollAmount();
    
    JLog("%s %d 획득", *UEnum::GetValueAsString(Row->ItemType), Amount);
    switch (Row->ItemType)
    {
    case EItemType::Mine:
    {
        UStatComponent* StatComponent = Who->GetComponentByClass<UStatComponent>();
        checkf(IsValid(StatComponent), TEXT("There is no StatComponent"));

        int CurrentHealth = StatComponent->GetInt(ECharacterStatType::Health, 0);
        CurrentHealth -= Amount;
        StatComponent->SetOrAdd(ECharacterStatType::Health, CurrentHealth);
        if (CurrentHealth <= 0)
        {
            JError("사망을 구현하세요");
            return;
        }

        break;
    }
        

    case EItemType::Coin:
    {
        UIngameGameInstance* GameInstance = Cast<UIngameGameInstance>(GetGameInstance());
        checkf(IsValid(GameInstance), TEXT("GameInstnace is not UIngameGameInstance"));

        GameInstance->AddScore(Amount);
        break;
    }

    case EItemType::HealthPack:
    {
        UStatComponent* StatComponent = Who->GetComponentByClass<UStatComponent>();
        checkf(IsValid(StatComponent), TEXT("There is no StatComponent"));

        int CurrentHealth = StatComponent->GetInt(ECharacterStatType::Health, 0);
        int MaxHealth = StatComponent->GetInt(ECharacterStatType::MaxHealth, 0);

        CurrentHealth += Amount;
        if (CurrentHealth > MaxHealth)
        {
            CurrentHealth = MaxHealth;
        }

        StatComponent->SetOrAdd(ECharacterStatType::Health, CurrentHealth);
        break;
    }

    default:
        break;
    }    
}

void AIngameGameMode::SetNextWave()
{
    int CurrentWaveIndex = IngameState->GetCurrentWaveIndex();
    IngameState->SetCurrentWaveIndex(++CurrentWaveIndex );
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

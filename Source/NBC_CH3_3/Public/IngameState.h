#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "IngameState.generated.h"

UCLASS()
class NBC_CH3_3_API AIngameState : public AGameStateBase
{
	GENERATED_BODY()

public:
    void SetCurrentPickUpCount(int PickupCount);
    void SetTotalPickUpCount(int Count);
    void SetCurrentWaveIndex(int Value);
    void SetTotalWaveCount(int Value);
    void SetStartTime(float Value);
    void SetRemainTime(float Value);

    int GetCurrentPickUpCount() const;
    int GetTotalPickUpCount() const;
    int GetCurrentWaveIndex() const;
    int GetTotalWaveCount() const;
    float GetStartTime() const;
    float GetWaveDuration() const;
    float GetRemainTime() const;

    DECLARE_MULTICAST_DELEGATE_OneParam(
        FOnRemainingTimeChanged,
        float
    );

    DECLARE_MULTICAST_DELEGATE_TwoParams(
        FOnPickupCountChanged
        , int   //PickupCount
        , int   //totalCount
    );

    DECLARE_MULTICAST_DELEGATE_OneParam(
        FOnCurrentWaveIndexChanged
        , int   //PickupCount
    );

    DECLARE_MULTICAST_DELEGATE_OneParam(
        FOnTotalWaveCountChanged
        , int   //PickupCount
    );

    FOnRemainingTimeChanged OnRemainTimeChanged;
    FOnPickupCountChanged OnPickupCountChanged;
    FOnCurrentWaveIndexChanged OnWaveIndexChanged;
    FOnTotalWaveCountChanged OnTotalWaveCountChanged;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    int CurrentPickUpCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    int TotalPickupCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    float WaveDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    int CurrentWaveIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    int TotalWaveCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    float RemainTime;

    float StartTime;
};

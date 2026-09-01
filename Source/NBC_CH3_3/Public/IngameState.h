#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "IngameState.generated.h"

UCLASS()
class NBC_CH3_3_API AIngameState : public AGameStateBase
{
	GENERATED_BODY()

public:
    void SetCurrentCoinAmount(int InAmount);
    void SetTargetCoinCount(int Count);
    void SetCurrentWaveIndex(int Value);
    void SetTotalWaveCount(int Value);
    void SetStartTime(float Value);
    void SetRemainTime(float Value);

    int GetCurrentCoinCount() const; 
    int GetTargetCoinCount() const;
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
        FCoinCountChanged
        , int   //PickupCount
        , int   //totalCount
    );

    DECLARE_MULTICAST_DELEGATE_TwoParams(
        FOnCurrentWaveIndexChanged
        , int   //current wave index
        , int   // totla wave count
    );

    FOnRemainingTimeChanged OnRemainTimeChanged;
    FCoinCountChanged OnCoinCountChanged;
    FOnCurrentWaveIndexChanged OnWaveIndexChanged;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    int CurrentCoinCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngameState|Properties")
    int TargetCoinCount;

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

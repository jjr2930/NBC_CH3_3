#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IngameGameMode.generated.h"

class AFieldItemBase;

UCLASS()
class NBC_CH3_3_API AIngameGameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    void PickupFieldItem(const AFieldItemBase& item);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    int TargetPickupCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    int CurrentPickupCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    int TotalWaveCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    int CurrentWave;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    TSoftObjectPtr<UWorld> NextStage;    
};

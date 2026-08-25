#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IngameGameMode.generated.h"

class AFieldItemBase;
class AIngameState;

UCLASS()
class NBC_CH3_3_API AIngameGameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    AIngameGameMode();
    void PickupFieldItem(const AFieldItemBase& item);
    
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    TSoftObjectPtr<UWorld> NextStage;    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    TSoftObjectPtr<UWorld> FailedLevel;
    
    AIngameState* IngameState;
};

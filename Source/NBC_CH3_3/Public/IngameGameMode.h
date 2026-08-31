#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enums.h"
#include "IngameGameMode.generated.h"

class AFieldItem;
class AIngameState;
struct FInventoryItemData;

UCLASS()
class NBC_CH3_3_API AIngameGameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    AIngameGameMode();
    /*void PickupFieldItem(AFieldItem& item, AActor& Who, EItemType* ItemType, int* Amount);*/
    void SetNextWave();
    void OnItemAdded(const FInventoryItemData& AddedItem);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    TSoftObjectPtr<UWorld> NextStage;    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode|Properties")
    TSoftObjectPtr<UWorld> FailedLevel;
    
    AIngameState* IngameState;
};

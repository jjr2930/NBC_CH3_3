#pragma once

#include "Enums.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FInventoryItemData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItemData")
    FName TableKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItemData")
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItemData")
    int StackCount;
};

UCLASS( )
class NBC_CH3_3_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    void AddItem(EItemType InItemType, FName& InTableKey, int amount);
    void RemoveItem(EItemType InItemType, FName& InTableKey, int amount);
    bool TryGetItem(EItemType InItemType, FName& TableKey, int* OutFound);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TObjectPtr<UDataTable> ConsumeItemTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TObjectPtr<UDataTable> QuestItemTable;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventoryItemData> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int ItemMaxCount;
};

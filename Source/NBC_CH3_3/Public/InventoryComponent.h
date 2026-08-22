#pragma once


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
    int TableKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItemData")
    int StackCount;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NBC_CH3_3_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void AddItem(int TableKey, int amount);
    void RemoveItem(int TableKey, int amount);
    bool TryGetItem(int TableKey, int* OutFound);
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TObjectPtr<UDataTable> ItemTable;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventoryItemData> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int ItemMaxCount;
};

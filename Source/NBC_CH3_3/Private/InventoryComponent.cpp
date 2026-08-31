#include "InventoryComponent.h"
#include "ItemDataRow.h"
#include "Engine/Engine.h"
#include "JUtility.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(int TableKey, int amount)
{
    if (!IsValid(ItemTable))
    {
        JError("Item table is not valid");
        return;
    }

    int FoundIndex = -1;
    TArray<FItemDataRowBase*> AllRows;
    ItemTable->GetAllRows(FString("Inventory"), AllRows);

    if (AllRows.IsEmpty())
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString(TEXT("DATA TALBE IS EMPTY")));
        return;
    }

    JError("Implement this section");

    if (TryGetItem(TableKey, &FoundIndex))
    {
        Items[FoundIndex].StackCount += amount;
    }
    else
    {
        Items.Add({ TableKey, amount });
    }
}

void UInventoryComponent::RemoveItem(int TableKey, int amount)
{
    int FoundIndex = -1;
    if (!TryGetItem(TableKey, &FoundIndex))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("TableKey : {%d} is not exist"), TableKey));
        return;
    }

    if (Items[FoundIndex].StackCount < amount)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("TableKey : {%d} is not Enough"), TableKey));
        return;
    }

    Items[FoundIndex].StackCount -= amount;
}

bool UInventoryComponent::TryGetItem(int TableKey, int* OutFoundIndex)
{
    int32 Size = Items.Num();
    for (int i = 0; i < Size; ++i) 
    {
        if (Items[i].TableKey == TableKey)
        {
            *OutFoundIndex = i;
            return true;
        }
    }

    
    *OutFoundIndex = -1;
    return false;
}



#include "InventoryComponent.h"
#include "ItemDataRow.h"
#include "Engine/Engine.h"


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
    int FoundIndex = -1;
    TArray<FItemDataRow*> AllRows;
    ItemTable->GetAllRows(FString("Inventory"), AllRows);

    if (AllRows.IsEmpty())
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString(TEXT("DATA TALBE IS EMPTY")));
        return;
    }

    for (auto iter : AllRows)
    {
        //like gear...
        if (!iter->IsStackable)
        {
            Items.Add({ TableKey, amount });
            return;
        }
    }

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
    for (auto Item : Items)
    {
        if (Item.TableKey == TableKey)
        {
            return true;
        }
    }

    return false;
}



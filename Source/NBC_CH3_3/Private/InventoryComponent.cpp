#include "InventoryComponent.h"
#include "ItemTableRowBase.h"
#include "Engine/Engine.h"
#include "JUtility.h"
#include "QuestItemTableRow.h"
#include "ConsumeItemTableRow.h"
#include "IngameGameMode.h"

void UInventoryComponent::AddItem(EItemType InItemType, FName& InTableKey, int InAmount)
{
    JASSERT(IsValid(ConsumeItemTable), "Consume item table is null or not setted");
    JASSERT(IsValid(QuestItemTable), "Quest item table is null or not setted");

    FItemTableRowBase* ItemRow = nullptr;
    switch (InItemType)
    {
    case EItemType::ConsumeItem:
        ItemRow = ConsumeItemTable->FindRow<FItemTableRowBase>(InTableKey, TEXT("TPS Player"));
        break;

    case EItemType::QuestItem:
        ItemRow = QuestItemTable->FindRow<FItemTableRowBase>(InTableKey, TEXT("TPS Player"));
        break;
    }

    FInventoryItemData* AddedInventoryItemData = nullptr;
    if (ItemRow->IsStackable)
    {
        int FoundIndex = -1;
        if (TryGetItem(InItemType, InTableKey, &FoundIndex))
        {
            Items[FoundIndex].StackCount += InAmount;
            AddedInventoryItemData = &Items[FoundIndex];
        }
        else
        {
            Items.Add({ InTableKey, InItemType, InAmount });
            AddedInventoryItemData = &Items.Last();
        }
    }
    else
    {
        Items.Add({ InTableKey, InItemType, InAmount });
        AddedInventoryItemData = &Items.Last();
    }

    AIngameGameMode* IngameGameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
    IngameGameMode->OnItemAdded(*AddedInventoryItemData);
}

void UInventoryComponent::RemoveItem(EItemType InItemType, FName& TableKey, int amount)
{
    int FoundIndex = -1;
    if (!TryGetItem(InItemType, TableKey, &FoundIndex))
    {
        JError("TableKey : {%s} is not exist", *TableKey.ToString());
        return;
    }

    if (Items[FoundIndex].StackCount < amount)
    {
        JError("TableKey : {%s} is not exist", *TableKey.ToString());
        return;
    }

    Items[FoundIndex].StackCount -= amount;
}

bool UInventoryComponent::TryGetItem(EItemType InItemType, FName& TableKey, int* OutFoundIndex)
{
    int32 Size = Items.Num();
    for (int i = 0; i < Size; ++i) 
    {
        if (Items[i].TableKey == TableKey
            && Items[i].ItemType == InItemType)
        {
            *OutFoundIndex = i;
            return true;
        }
    }
    
    *OutFoundIndex = -1;
    return false;
}


void UInventoryComponent::Clear()
{
    int32 Size = Items.Num();
    Items.Empty();
}
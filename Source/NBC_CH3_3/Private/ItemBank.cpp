#include "ItemBank.h"
#include "QuestItemTableRow.h"
#include "ConsumeItemTableRow.h"

// Sets default values
AItemBank::AItemBank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FItemTableRowBase* AItemBank::GetItemRow(EItemType ItemType, const FName& Key)
{
    switch (ItemType)
    {
    case EItemType::QuestItem:
        return Cast<FItemTableRowBase>(QuestItemTable->FindRow<FQuestItemTableRow>(Key, "ItemBank"));
        
    case EItemType::ConsumeItem:
        return Cast<FItemTableRowBase>(ConsumeItemTable->FindRow<FConsumeItemTableRow>(Key, "ItemBank"));

    default:
        break;
    }
}
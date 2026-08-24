#include "FieldCoin.h"
#include "StatComponent.h"
#include "InventoryComponent.h"
#include "JUtility.h"
#include "ItemDataRow.h"
#include "FieldItemSpawnRow.h"

AFieldCoin::AFieldCoin()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFieldCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFieldCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFieldCoin::OnPicked(TObjectPtr<AActor> Who)
{
    UInventoryComponent* Inventory = Who->GetComponentByClass<UInventoryComponent>();
    if (!IsValid(Inventory))
    {
        JError("%s Does not have InventoryComponent", *Who->GetName());
        return;
    }

    Inventory->AddItem(Row->ItemTableKey, Row->RollAmount());

    Destroy();
}
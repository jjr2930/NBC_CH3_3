#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums.h"
#include "ItemBank.generated.h"

class UDataTable;
struct FItemTableRowBase;

UCLASS()
class NBC_CH3_3_API AItemBank : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AItemBank();
    FItemTableRowBase* GetItemRow(EItemType ItemType, const FName& Key);

    TObjectPtr<UDataTable> QuestItemTable;
    TObjectPtr<UDataTable> ConsumeItemTable;
};

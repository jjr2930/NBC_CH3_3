#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBank.generated.h"

class UDataTable;

UCLASS()
class NBC_CH3_3_API AItemBank : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBank();

    TObjectPtr<UDataTable> QuestItemTable;
    TObjectPtr<UDataTable> FieldItemTable;
};

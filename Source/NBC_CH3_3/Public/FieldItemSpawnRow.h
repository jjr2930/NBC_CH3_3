#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "FieldItemSpawnRow.generated.h"

class AFieldItemBase;

USTRUCT(BlueprintType)
struct NBC_CH3_3_API  FFieldItemSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    FFieldItemSpawnRow();
    int RollAmount();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawnRow|Properties")
    int ItemTableKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawnRow|Properties")
    TSubclassOf<AFieldItemBase> FieldItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataRow")
    int AmountMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataRow")
    int AmountMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawnRow|Properties")
    float DropRate;
};

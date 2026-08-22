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

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawnRow|Properties")
    FName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawnRow|Properties")
    TSubclassOf<AFieldItemBase> ItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawnRow|Properties")
    float DropRate;
};

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Enums.h"
#include "FieldItemSpawnRow.generated.h"

class AFieldItem;

USTRUCT(BlueprintType)
struct NBC_CH3_3_API  FFieldItemSpawnRow : public FTableRowBase
{
    GENERATED_BODY()


//TODO : Protected Field 들을 Public으로 만들기
public:
    FFieldItemSpawnRow();
    int RollAmount();
    EItemType GetItemType();
    float GetDropRate();
    EBuffType GetBuffType();
    const FName& GetTableKey() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "===FIELD ITEM===")
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "===FIELD ITEM===")
    int AmountMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "===FIELD ITEM===")
    int AmountMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "===FIELD ITEM===")
    float DropRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "===FIELD ITEM===")
    EBuffType BuffType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "===FIELD ITEM===")
    FName TableKey;
};

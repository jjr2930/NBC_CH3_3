#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "ItemDataRow.generated.h"

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FItemDataRow : public FTableRowBase
{
    GENERATED_BODY()

public:
	FItemDataRow();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemDataRow")
    int Key;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataRow")
    FName Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataRow")
    bool IsStackable;
};

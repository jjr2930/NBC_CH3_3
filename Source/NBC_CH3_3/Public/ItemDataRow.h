#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Enums.h"
#include "ItemDataRow.generated.h"

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FItemDataRowBase : public FTableRowBase
{
    GENERATED_BODY()

public:
	FItemDataRowBase();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataRow")
    FName DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataRow")
    bool IsStackable;
};

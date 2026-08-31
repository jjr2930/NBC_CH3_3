#pragma once

#include <Engine/DataTable.h>  
#include "CoreMinimal.h"
#include "ItemDataRow.h"
#include "ConsumeItemTableRow.generated.h"

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FConsumeItemTableRow : public FItemDataRowBase
{
    GENERATED_BODY();

public:
	FConsumeItemTableRow();
	~FConsumeItemTableRow();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBuffType BuffType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuffRowName;
};

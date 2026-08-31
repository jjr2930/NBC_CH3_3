#pragma once

#include <Engine/DataTable.h>  
#include "CoreMinimal.h"
#include "ItemTableRowBase.h"
#include "Enums.h"
#include "ConsumeItemTableRow.generated.h"

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FConsumeItemTableRow : public FItemTableRowBase
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

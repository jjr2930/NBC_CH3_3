#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "ItemTableRowBase.generated.h"

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FItemTableRowBase : public FTableRowBase
{
    GENERATED_BODY();

public:
	FItemTableRowBase();
	~FItemTableRowBase();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemDisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsStackable;
};

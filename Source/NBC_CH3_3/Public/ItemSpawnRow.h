#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"


USTRUCT(BlueprintType)
struct NBC_CH3_3_API FItemSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
	FItemSpawnRow();
	~FItemSpawnRow();
};

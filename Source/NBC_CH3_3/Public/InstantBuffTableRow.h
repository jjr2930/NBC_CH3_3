#pragma once

#include "CoreMinimal.h"
#include "BuffTableRowBase.h"
#include "InstantBuffTableRow.generated.h"

class FBuff;

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FInstantBuffTableRow : public FBuffTableRowBase
{
    GENERATED_BODY();

public:
	FInstantBuffTableRow();
	~FInstantBuffTableRow();
};

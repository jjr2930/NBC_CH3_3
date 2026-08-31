#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestItemTableRow.generated.h"

USTRUCT(BlueprintType)
struct NBC_CH3_3_API FQuestItemTableRow : public FTableRowBase
{
    GENERATED_BODY();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DiplayName;
};

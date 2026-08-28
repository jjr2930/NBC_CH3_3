#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "BuffTableRowBase.h"
//TODO: 아 그냥 꺽쇠 괄호 지우고 모두 따옴표로 참조해!
#include "Engine/DataTable.h"
#include "DurationBuffTableRow.generated.h"


USTRUCT(BlueprintType)
struct NBC_CH3_3_API FDurationBuffTableRow : public FBuffTableRowBase
{
    GENERATED_BODY()

public:
    FDurationBuffTableRow();
	~FDurationBuffTableRow();

    virtual FBuff* ToBuff() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    float StartTime;
};

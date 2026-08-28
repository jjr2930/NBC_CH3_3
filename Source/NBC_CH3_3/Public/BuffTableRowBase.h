#pragma once

#include "Engine/DataTable.h"

#include "CoreMinimal.h"
#include "Enums.h"

#include "BuffTableRowBase.generated.h"

class FBuff;
USTRUCT(BlueprintType)
struct NBC_CH3_3_API FBuffTableRowBase : public FTableRowBase
{
    GENERATED_BODY()

public:
    FBuffTableRowBase();
	~FBuffTableRowBase();

    virtual FBuff* ToBuff() PURE_VIRTUAL(FBuff::ToBuff, return nullptr; );
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    ECharacterStatType TargetStat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    EStatOperatorType Operator;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    bool IsIntValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    int IntValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== BUFF ===")
    float FloatValue;
};

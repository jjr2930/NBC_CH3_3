#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    QuestItem     UMETA(DisplayName = "QuestItem"),
    ConsumeItem   UMETA(DisplayName = "ConsumeItem"),
};


UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
    Health      UMETA(DisplayName = "Health"),
    MaxHealth   UMETA(DisplayName = "Max Health"),
    MovingSpeed UMETA(DisplayName = "Moving Speed"),
};

UENUM(BlueprintType)
enum class EStatOperatorType : uint8
{
    Add         UMETA(DisplayName = "Add"),
    Subtract    UMETA(DisplayName = "Subtract"),
    Multiply    UMETA(DisplayName = "Multiply"),
    Divide      UMETA(DisplayName = "Divide")
};

UENUM(BlueprintType)
enum class EBuffType : uint8
{
    Instant     UMETA(DisplayName = "Instant"),
    Duration    UMETA(DisplayName = "Duration")
};
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Coin            UMETA(DisplayName = "Coin"),
    HealthPack    UMETA(DisplayName = "HealthPack"),
    Mine          UMETA(DisplayName = "Mine"),
};


UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
    Health      UMETA(DisplayName = "Health"),
    MaxHealth   UMETA(DisplayName = "Max Health")
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
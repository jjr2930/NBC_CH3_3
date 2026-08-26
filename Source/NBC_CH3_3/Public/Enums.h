#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Coin            UMETA(DisplayName = "Coin")
    , HealthPack    UMETA(DisplayName = "HealthPack")
    , Mine          UMETA(DisplayName = "Mine")
};

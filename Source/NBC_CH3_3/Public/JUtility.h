#pragma once

#include "CoreMinimal.h"

class JUtility
{
public:
    JUtility();
	~JUtility();

    static void Log(FString Format, ...);
    static void Warning(FString Format, ...);
    static void Error(FString Format, ...);

protected:
    static void Print(FString Format , FColor Color, ...);
};

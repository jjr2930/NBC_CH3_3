#pragma once

#include "CoreMinimal.h"
#include "Enums.h"

class FBuff;
class UWorld;
struct FBuffTableRowBase;

class NBC_CH3_3_API FBuffFactory
{
public:
	FBuffFactory();
	~FBuffFactory();

    static FBuff* CreateBuff(UWorld* InWorld, const EBuffType buffType, const FBuffTableRowBase* BuffData);
};

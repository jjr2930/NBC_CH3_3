#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IngameGameInstance.generated.h"

UCLASS()
class NBC_CH3_3_API UIngameGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    void AddScore(int InAmount);
    void ClearScore();

    int GetScore();

protected:
    int Score;
};

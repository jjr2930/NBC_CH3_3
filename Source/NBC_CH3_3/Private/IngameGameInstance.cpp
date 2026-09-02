#include "IngameGameInstance.h"

void UIngameGameInstance::AddSeconds(float InAmount)
{
    Score += InAmount;
}

void UIngameGameInstance::ClearScore()
{
    Score = 0;
}

float UIngameGameInstance::GetScore()
{
    return Score;
}

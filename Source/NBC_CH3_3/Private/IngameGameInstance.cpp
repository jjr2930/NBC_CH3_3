#include "IngameGameInstance.h"

void UIngameGameInstance::AddScore(int InAmount)
{
    Score += InAmount;
}

void UIngameGameInstance::ClearScore()
{
    Score = 0;
}

int UIngameGameInstance::GetScore()
{
    return Score;
}

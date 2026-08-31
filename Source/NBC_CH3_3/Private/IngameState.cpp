#include "IngameState.h"


void AIngameState::SetCurrentCoinAmount(int InAmount)
{
    CurrentCoinCount = InAmount;

    OnCoinCountChanged.Broadcast(CurrentCoinCount, TargetCoinCount);
}

void AIngameState::SetCurrentPoint(int InValue)
{
    this->CurrentCoinCount = InValue;

    OnCoinCountChanged.Broadcast(CurrentCoinCount, TargetCoinCount);
}

void AIngameState::SetTargetCoinCount(int InValue)
{
    TargetCoinCount = InValue;
      
    OnCoinCountChanged.Broadcast(CurrentCoinCount, TargetCoinCount);
}

void AIngameState::SetCurrentWaveIndex(int InValue)
{
    CurrentWaveIndex = InValue; 

    OnWaveIndexChanged.Broadcast(CurrentWaveIndex, TotalWaveCount);
}

void AIngameState::SetTotalWaveCount(int InValue)
{
    TotalWaveCount = InValue;

    OnWaveIndexChanged.Broadcast(CurrentWaveIndex, TotalWaveCount);
}

void AIngameState::SetStartTime(float InValue)
{
    StartTime = InValue;
}

void AIngameState::SetRemainTime(float InValue)
{
    RemainTime = InValue;

    OnRemainTimeChanged.Broadcast(RemainTime);
}

int AIngameState::GetCurrentCoinCount() const
{
    return CurrentCoinCount;
}

int AIngameState::GetTargetCoinCount() const
{
    return TargetCoinCount;
}

int AIngameState::GetCurrentWaveIndex() const
{
    return CurrentWaveIndex;
}

int AIngameState::GetTotalWaveCount() const
{
    return TotalWaveCount;
}

float AIngameState::GetStartTime() const
{
    return StartTime;
}

float AIngameState::GetWaveDuration() const
{
    return WaveDuration;
}

float AIngameState::GetRemainTime() const
{
    return RemainTime;
}

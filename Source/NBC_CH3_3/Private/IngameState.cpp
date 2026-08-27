#include "IngameState.h"


void AIngameState::AddCurrentPoint(int InAmount)
{
    CurrentPoint += InAmount;
}

void AIngameState::SetCurrentPoint(int InValue)
{
    this->CurrentPoint = InValue;

    OnPickupCountChanged.Broadcast(CurrentPoint, TargetPoint);
}

void AIngameState::SetTargetPoint(int InValue)
{
    TargetPoint = InValue;
      
    OnPickupCountChanged.Broadcast(CurrentPoint, TargetPoint);
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

int AIngameState::GetCurrentPickUpCount() const
{
    return CurrentPoint;
}

int AIngameState::GetTotalPickUpCount() const
{
    return TargetPoint;
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

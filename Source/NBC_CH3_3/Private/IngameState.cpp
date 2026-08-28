#include "IngameState.h"


void AIngameState::AddCurrentPoint(int InAmount)
{
    CurrentPoint += InAmount;

    OnPointChanged.Broadcast(CurrentPoint, TargetPoint);
}

void AIngameState::SetCurrentPoint(int InValue)
{
    this->CurrentPoint = InValue;

    OnPointChanged.Broadcast(CurrentPoint, TargetPoint);
}

void AIngameState::SetTargetPoint(int InValue)
{
    TargetPoint = InValue;
      
    OnPointChanged.Broadcast(CurrentPoint, TargetPoint);
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

int AIngameState::GetCurrentPoint() const
{
    return CurrentPoint;
}

int AIngameState::GetTargetPoint() const
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

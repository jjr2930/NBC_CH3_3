#include "IngameState.h"


void AIngameState::SetCurrentPickUpCount(int InValue)
{
    this->CurrentPickUpCount = InValue;

    OnPickupCountChanged.Broadcast(CurrentPickUpCount, TotalPickupCount);
}

void AIngameState::SetTotalPickUpCount(int InValue)
{
    TotalPickupCount = InValue;

    OnPickupCountChanged.Broadcast(CurrentPickUpCount, TotalPickupCount);
}

void AIngameState::SetCurrentWaveIndex(int InValue)
{
    CurrentWaveIndex = InValue;
}

void AIngameState::SetTotalWaveCount(int InValue)
{
    TotalWaveCount = InValue;
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
    return CurrentPickUpCount;
}

int AIngameState::GetTotalPickUpCount() const
{
    return TotalPickupCount;
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

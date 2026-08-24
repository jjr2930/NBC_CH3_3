// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameState.h"

void AIngameState::SetCurrentPickUpCount(int Value)
{
    this->CurrentPickUpCount = Value;
}

void AIngameState::SetTotalPickUpCount(int Value)
{
    this->TotalPickupCount = Value; 
}

int AIngameState::GetCurrentPickUpCount() const
{
    return CurrentPickUpCount;
}

int AIngameState::GetTotalPickUpCount() const
{
    return TotalPickupCount;
}

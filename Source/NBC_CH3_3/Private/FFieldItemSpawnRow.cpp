#include "FieldItemSpawnRow.h"

FFieldItemSpawnRow::FFieldItemSpawnRow()
{
}

int FFieldItemSpawnRow::RollAmount()
{
    return FMath::RandRange(AmountMin, AmountMax);
}

EItemType FFieldItemSpawnRow::GetItemType()
{
    return ItemType;
}

float FFieldItemSpawnRow::GetDropRate()
{
    return DropRate;
}

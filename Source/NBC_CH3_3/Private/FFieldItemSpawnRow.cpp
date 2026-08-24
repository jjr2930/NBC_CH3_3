#include "FieldItemSpawnRow.h"

FFieldItemSpawnRow::FFieldItemSpawnRow()
{
}

int FFieldItemSpawnRow::RollAmount()
{
    return FMath::RandRange(AmountMin, AmountMax);
}

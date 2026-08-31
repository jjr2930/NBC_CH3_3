#include "InstantBuffTableRow.h"
#include "Buff.h"

FBuff* FInstantBuffTableRow::ToBuff()
{
    FBuff* NewBuff = new FInstantBuff(TargetStat
        , Operator
        , IsIntValue
        , IntValue
        , FloatValue);

    return NewBuff;
}

FInstantBuffTableRow::FInstantBuffTableRow()
{
}

FInstantBuffTableRow::~FInstantBuffTableRow()
{
}

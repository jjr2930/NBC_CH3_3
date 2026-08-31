#include "InstantBuffTableRow.h"
#include "Buff.h"

FBuff* FInstantBuffTableRow::ToBuff()
{
    return new FInstantBuff(TargetStat
        , Operator
        , IsIntValue
        , IntValue
        , FloatValue);
}

FInstantBuffTableRow::FInstantBuffTableRow()
{
}

FInstantBuffTableRow::~FInstantBuffTableRow()
{
}

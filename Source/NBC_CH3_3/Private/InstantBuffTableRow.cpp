#include "Buff.h"
#include "InstantBuffTableRow.h"

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

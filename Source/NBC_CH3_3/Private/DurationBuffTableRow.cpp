#include "DurationBuffTableRow.h"
#include "Buff.h"

FDurationBuffTableRow::FDurationBuffTableRow()
{
}

FDurationBuffTableRow::~FDurationBuffTableRow()
{
}

FBuff* FDurationBuffTableRow::ToBuff()
{
    return new FDurationBuff(TargetStat
        , Operator , IsIntValue , IntValue
        , FloatValue , Duration, StartTime);
}

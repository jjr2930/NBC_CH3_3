#include "BuffFactory.h"
#include "Buff.h"
#include "BuffTableRowBase.h"
#include "DurationBuffTableRow.h"
#include "InstantBuffTableRow.h"
#include "JUtility.h"

#include <Engine/World.h>

FBuffFactory::FBuffFactory()
{
}

FBuffFactory::~FBuffFactory()
{
}

FBuff* FBuffFactory::CreateBuff(UWorld* InWorld, const EBuffType BuffType, const FBuffTableRowBase* BuffData)
{
    switch (BuffType)
    {
    case EBuffType::Duration:
    {
        const FDurationBuffTableRow* DurationBuffTable = static_cast<const FDurationBuffTableRow*>(BuffData);
        return  new FDurationBuff(DurationBuffTable->TargetStat
            , DurationBuffTable->Operator
            , DurationBuffTable->IsIntValue
            , DurationBuffTable->IntValue
            , DurationBuffTable->FloatValue
            , DurationBuffTable->Duration
            , InWorld->TimeSeconds);
    }

    case EBuffType::Instant:
    {
        const FInstantBuffTableRow* InstantBuffTable = static_cast<const FInstantBuffTableRow*>(BuffData);
        return new FInstantBuff(InstantBuffTable->TargetStat
            , InstantBuffTable->Operator
            , InstantBuffTable->IsIntValue
            , InstantBuffTable->IntValue
            , InstantBuffTable->FloatValue);
    }
    default:
        JASSERT_NULLPTR(false
            , "BuffType %s notsupported"
            ,  *GET_ENUM_STRING(EBuffType, BuffType));
    }
}


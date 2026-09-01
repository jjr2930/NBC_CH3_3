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
        const FDurationBuffTableRow* DurationBuffTableRow = static_cast<const FDurationBuffTableRow*>(BuffData);
        return  new FDurationBuff(DurationBuffTableRow->TargetStat
            , DurationBuffTableRow->Operator
            , DurationBuffTableRow->IsIntValue
            , DurationBuffTableRow->IntValue
            , DurationBuffTableRow->FloatValue
            , DurationBuffTableRow->Duration
            , InWorld->TimeSeconds
            , DurationBuffTableRow->IconTexture);
    }

    case EBuffType::Instant:
    {
        const FInstantBuffTableRow* InstantBuffTableRow = static_cast<const FInstantBuffTableRow*>(BuffData);
        return new FInstantBuff(InstantBuffTableRow->TargetStat
            , InstantBuffTableRow->Operator
            , InstantBuffTableRow->IsIntValue
            , InstantBuffTableRow->IntValue
            , InstantBuffTableRow->FloatValue);
    }
    default:
        JASSERT_NULLPTR(false
            , "BuffType %s notsupported"
            ,  *GET_ENUM_STRING(EBuffType, BuffType));
    }
}


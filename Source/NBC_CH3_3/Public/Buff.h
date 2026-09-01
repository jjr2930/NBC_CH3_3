#pragma once

#include "Enums.h"
#include "CoreMinimal.h"
#include "StatComponent.h"
#include "JUtility.h"

#include <exception>

class NBC_CH3_3_API FBuff
{
public:
    FBuff(){}
    FBuff(ECharacterStatType InTargetStat, EStatOperatorType InOperator, bool InIsIntValue, int InIntValue, float InFloatValue)
        : TargetStat(InTargetStat)
        , Operator(InOperator)
        , IsIntValue(InIsIntValue)
        , IntValue(InIntValue)
        , FloatValue(InFloatValue)
        , bPendingRemoval(false)
    {
    }
    virtual ~FBuff()
    {
        //JLog("Destroy Buff");
    }
    
    bool GetPendingRemoval()
    {
        return bPendingRemoval;
    }

    EBuffType GetBuffType() const
    {
        return BuffType;
    }

    virtual void Tick(UStatComponent* StatComponent) = 0;
    virtual void GetBuffedStat(ECharacterStatType InStatType, int* OutStat) {}
    virtual void GetBuffedStat(ECharacterStatType InStatType, float* OutStat) {}

protected:
    EBuffType BuffType;
    ECharacterStatType TargetStat;
    EStatOperatorType Operator;
    bool IsIntValue;
    int IntValue;
    float FloatValue;
    bool bPendingRemoval;
};

class NBC_CH3_3_API FInstantBuff : public FBuff
{
public:
    FInstantBuff(ECharacterStatType InTargetStat, EStatOperatorType InOperator, bool InIsIntValue, int InIntValue, float InFloatValue)
        : FBuff(InTargetStat, InOperator, InIsIntValue, InIntValue, InFloatValue)
    {
        BuffType = EBuffType::Instant;
    }

    virtual ~FInstantBuff() 
    {
        //JLog("Destory Instant buff");
    }

    virtual void Tick(UStatComponent* StatComponent) override
    {
        if (IsIntValue)
        {
            TickInt(StatComponent);
        }
        else
        {
            TickFloat(StatComponent);
        }

        bPendingRemoval = true;
    }

    void TickInt(UStatComponent* StatComponent)
    {
        JASSERT(StatComponent->HasStat(TargetStat, IsIntValue),
            "%s does not have stat(%s)"
            , *StatComponent->GetOwner()->GetName()
            , *GET_ENUM_STRING(ECharacterStatType, TargetStat));

        int CurrentValue = StatComponent->GetInt(TargetStat);
        switch (Operator)
        {
            case EStatOperatorType::Add:
                CurrentValue += IntValue;
                break;

            case EStatOperatorType::Subtract:
                CurrentValue -= IntValue;
                break;

            case EStatOperatorType::Multiply:
                CurrentValue *= IntValue;
                break;

            case EStatOperatorType::Divide:
            {
                if (IntValue == 0) 
                    throw std::runtime_error("Can not divde by zero");
                  
                CurrentValue /= IntValue;
                break;
            }
        }

        StatComponent->SetOrInsert(TargetStat, CurrentValue);
    }

    void TickFloat(UStatComponent* StatComponent)
    {
        JASSERT(StatComponent->HasStat(TargetStat, IsIntValue)
            , "%s is not have %s"
            , *StatComponent->GetOwner()->GetName()
            , *GET_ENUM_STRING(ECharacterStatType, TargetStat)
        );

        float CurrentValue = StatComponent->GetFloat(TargetStat);
        switch (Operator)
        {
            case EStatOperatorType::Add:
                CurrentValue += FloatValue;
                break;

            case EStatOperatorType::Subtract:
                CurrentValue -= FloatValue;
                break;

            case EStatOperatorType::Multiply:
                CurrentValue *= FloatValue;
                break;

            case EStatOperatorType::Divide:
            {
                if (FMath::IsNearlyZero(FloatValue) == 0)
                    throw std::runtime_error("Can not divde by zero");

                CurrentValue /= IntValue;
                break;
            }
        }
    }

    //nothing to do 
    virtual void GetBuffedStat(ECharacterStatType InStatType, float* OutStat) override {}
    virtual void GetBuffedStat(ECharacterStatType InStatType, int* OutStat) override {}
};

class NBC_CH3_3_API FDurationBuff : public FBuff
{
public:
    FDurationBuff(ECharacterStatType InTargetType, EStatOperatorType InOperator, bool InIsIntValue, int InIntValue, float InFloatValue, float InDuration, float InStartTime, TObjectPtr<UTexture2D> InIconTexture)
        : FBuff(InTargetType, InOperator, InIsIntValue, InIntValue, InFloatValue)
        , Duration(InDuration), StartTime(InStartTime), IconTexture(InIconTexture)
    {
        BuffType = EBuffType::Duration;
    }

    virtual ~FDurationBuff()
    {
        //JLog("Destroy Duration buff");
    }


    virtual void Tick(UStatComponent* StatComponent) override
    {
        float Now = (float)StatComponent->GetWorld()->GetTimeSeconds();
        if (Now - StartTime >= Duration)
        {
            bPendingRemoval = true;
        }
    }

    virtual void GetBuffedStat(ECharacterStatType InStatType, int* OutStat) override 
    {
        FBuff::GetBuffedStat(InStatType, OutStat);

        if (InStatType != TargetStat)
            return;

        switch (Operator)
        {
        case EStatOperatorType::Add:
            *OutStat += IntValue;
            break;

        case EStatOperatorType::Subtract:
            *OutStat -= IntValue;
            break;

        case EStatOperatorType::Multiply:
            *OutStat *= IntValue;
            break;

        case EStatOperatorType::Divide:
        {
            if (IntValue == 0)
                throw std::runtime_error("Divide By Zero Exception");

            *OutStat /= IntValue;
            break;
        }
        default:
            break;
        }
    }

    virtual void GetBuffedStat(ECharacterStatType InStatType, float* OutStat) override
    {
        FBuff::GetBuffedStat(InStatType, OutStat);

        if (InStatType != TargetStat)
            return;

        switch (Operator)
        {
        case EStatOperatorType::Add:
            *OutStat += FloatValue;
            break;

        case EStatOperatorType::Subtract:
            *OutStat -= FloatValue;
            break;

        case EStatOperatorType::Multiply:
            *OutStat *= FloatValue;
            break;

        case EStatOperatorType::Divide:
        {
            if (FloatValue == 0)
                throw std::runtime_error("Divide By Zero Exception");

            *OutStat /= FloatValue;
            break;
        }
        default:
            break;
        }
    }

    float GetDuration()
    {
        return Duration;
    }

    float GetStartTime()
    {
        return StartTime;
    }

    TObjectPtr<UTexture2D> GetIconTexture()
    {
        return IconTexture;
    }

protected:
    float Duration;
    float StartTime;

    TObjectPtr<UTexture2D> IconTexture;
};

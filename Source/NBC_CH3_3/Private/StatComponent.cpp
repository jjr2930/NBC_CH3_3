#include "StatComponent.h"
#include "JUtility.h"
#include "Buff.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UStatComponent::SetOrInsert(ECharacterStatType InStatType, int InValue)
{
    JLog("%s, %s, Set to %d",
        *GetOwner()->GetName()
        , *StaticEnum<ECharacterStatType>()->GetNameStringByValue((int64)InStatType)
        , InValue);

    IntStats[InStatType] = InValue;
  
    OnIntStatChangedCallbacks.Broadcast(InStatType, InValue);
}

void UStatComponent::SetOrInsert(ECharacterStatType InStatType, float InValue)
{
    JLog("%s, %s, Set to %f",
        *GetOwner()->GetName()
        , *StaticEnum<ECharacterStatType>()->GetNameStringByValue((int64)InStatType)
        , InValue);

    FloatStats[InStatType] = InValue;

    OnFloatStatChangedCallbacks.Broadcast(InStatType, InValue);
}

int UStatComponent::GetInt(ECharacterStatType StatType, int DefaultValue )
{
    if (IntStats.Contains(StatType))
    {
        return *IntStats.Find(StatType);
    }

    else
    {
        IntStats.Add(StatType, DefaultValue);
        return DefaultValue;
    }
}

float UStatComponent::GetFloat(ECharacterStatType StatType, float DefaultValue)
{
    if (FloatStats.Contains(StatType))
    {
        return *FloatStats.Find(StatType);
    }

    else
    {
        FloatStats.Add(StatType, DefaultValue);
        return DefaultValue;
    }
}

bool UStatComponent::HasStat(ECharacterStatType InStatType, bool IsInt)
{
    if (IsInt)
    {
        return IntStats.Contains(InStatType);
    }
    else
    {
        return FloatStats.Contains(InStatType);
    }
}

void UStatComponent::AddBuff(FBuff* Buff)
{
    Buffs.Add(Buff);
}

UStatComponent::FOnIntStatChangedEvent* UStatComponent::GetIntCallbacks()
{
    return &OnIntStatChangedCallbacks;
}

UStatComponent::FOnFloatStatChangedEvent* UStatComponent::GetFloatCallback()
{
    return &OnFloatStatChangedCallbacks;
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    int Count = Buffs.Num();
    for (int i = Count - 1; i >= 0; --i)
    {
        Buffs[i]->Tick(this);
        if (Buffs[i]->GetPendingRemoval())
        {
            delete Buffs[i];
            Buffs.RemoveAt(i);
        }
    }
}



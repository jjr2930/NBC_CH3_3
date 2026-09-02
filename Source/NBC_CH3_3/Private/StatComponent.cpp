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
    /*JLog("%s, %s, Set to %d",
        *GetOwner()->GetName()
        , *StaticEnum<ECharacterStatType>()->GetNameStringByValue((int64)InStatType)
        , InValue);*/

    IntStats[InStatType] = InValue;

    if (IntStatClampCallback.IsBound())
        IntStatClampCallback.Execute(InStatType);

    OnIntStatChangedCallbacks.Broadcast(InStatType, InValue);
}

void UStatComponent::SetOrInsert(ECharacterStatType InStatType, float InValue)
{
  /*  JLog("%s, %s, Set to %f",
        *GetOwner()->GetName()
        , *StaticEnum<ECharacterStatType>()->GetNameStringByValue((int64)InStatType)
        , InValue);*/

    FloatStats[InStatType] = InValue;

    if (FloatStatClampCallback.IsBound())
        FloatStatClampCallback.Execute(InStatType);

    OnFloatStatChangedCallbacks.Broadcast(InStatType, InValue);
}

void UStatComponent::SetOrInsertWithoutNotify(ECharacterStatType InStatType, int InValue)
{
    /*JLog("%s, %s, Set to %d Without Notify" ,
        *GetOwner()->GetName()
        , *StaticEnum<ECharacterStatType>()->GetNameStringByValue((int64)InStatType)
        , InValue);*/

    IntStats[InStatType] = InValue;
}

void UStatComponent::SetOrInsertWithoutNotify(ECharacterStatType InStatType, float InValue)
{
    /*JLog("%s, %s, Set to %f Without Notify",
        *GetOwner()->GetName()
        , *StaticEnum<ECharacterStatType>()->GetNameStringByValue((int64)InStatType)
        , InValue);*/

    FloatStats[InStatType] = InValue;
}

int UStatComponent::GetInt(ECharacterStatType InStatType, int InDefaultValue )
{
    int BuffedStat = 0;
    if (IntStats.Contains(InStatType))
    {
        BuffedStat = *IntStats.Find(InStatType);
    }

    else
    {
        IntStats.Add(InStatType, InDefaultValue);
        BuffedStat = InDefaultValue;
    }

    for (FBuff* Buff : Buffs)
    {
        Buff->GetBuffedStat(InStatType, &BuffedStat);
    }

    return BuffedStat;
}

float UStatComponent::GetFloat(ECharacterStatType InStatType, float DefaultValue)
{
    float BuffedStat = 0.0f;
    if (FloatStats.Contains(InStatType))
    {
         BuffedStat = *FloatStats.Find(InStatType);
    }

    else
    {
        FloatStats.Add(InStatType, DefaultValue);
        BuffedStat = DefaultValue;
    }

    //TODO: Duplicated code with Getint();

    for (FBuff* Buff : Buffs)
    {
        Buff->GetBuffedStat(InStatType, &BuffedStat);
    }

    return BuffedStat;
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

    //JLog("Buff added");

    BuffAddedCallbacks.Broadcast(Buff);
}

UStatComponent::FOnIntStatChangedEvent* UStatComponent::GetIntCallbacks()
{
    return &OnIntStatChangedCallbacks;
}

UStatComponent::FOnFloatStatChangedEvent* UStatComponent::GetFloatCallback()
{
    return &OnFloatStatChangedCallbacks;
}

UStatComponent::FIntStatClampCallback* UStatComponent::GetDelegateIntStatClamp()
{
    return &IntStatClampCallback;
}

UStatComponent::FFloatStatClampCallback* UStatComponent::GetDelegateFloatStatClamp()
{
    return &FloatStatClampCallback;
}

UStatComponent::FOnBuffAddedEvent* UStatComponent::GetDelegateBuffAdded()
{
    return &BuffAddedCallbacks;
}

UStatComponent::FOnBuffRemovedEvent* UStatComponent::GetDelegateBuffRemoved()
{
    return &BuffRemovedCallbacks;
}

const TArray<FBuff*>* UStatComponent::GetBuffs()
{
    return &Buffs;
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
     
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
            FBuff* Old = Buffs[i];
            Buffs.RemoveAt(i);
            BuffRemovedCallbacks.Broadcast(Old); 
            delete Old;
        }
    }
}



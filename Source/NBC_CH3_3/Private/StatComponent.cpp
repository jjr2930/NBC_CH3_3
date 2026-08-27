


#include "StatComponent.h"


// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UStatComponent::SetOrAdd(ECharacterStatType statType, int value)
{
    IntStats.FindOrAdd(statType, value);
}

void UStatComponent::SetOrAdd(ECharacterStatType statType, float Value)
{
    FloatStats.FindOrAdd(statType, Value);
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

UStatComponent::FOnIntStatChangedEvent* UStatComponent::GetIntCallbacks()
{
    return &IntStatChangedCallbacks;
}

UStatComponent::FOnFloatStatChangedEvent* UStatComponent::GetFloatCallback()
{
    return &FloatStatChangedCallbacks;
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

	// ...
}



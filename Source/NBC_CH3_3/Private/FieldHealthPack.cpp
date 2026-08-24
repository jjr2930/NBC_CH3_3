#include "FieldHealthPack.h"
#include "StatComponent.h"
#include "JUtility.h"

// Sets default values
AFieldHealthPack::AFieldHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFieldHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFieldHealthPack::OnPicked(TObjectPtr<AActor> Who)
{
    UStatComponent* StatComponent = Who->GetComponentByClass<UStatComponent>();
    if (!IsValid(StatComponent))
    {
        JError("%s Does not have stat component", *Who->GetName());
        return;
    }

    int CurrentHealth = StatComponent->GetInt(ECharacterStatType::Health, 0);
    int MaxHealth = StatComponent->GetInt(ECharacterStatType::MaxHealth, 100);

    CurrentHealth += HealingAmount;
    if (CurrentHealth > MaxHealth)
        CurrentHealth = MaxHealth;

    StatComponent->SetOrAdd(ECharacterStatType::Health, CurrentHealth);
}
#include "FieldCoin.h"
#include "StatComponent.h"

AFieldCoin::AFieldCoin()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFieldCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFieldCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFieldCoin::OnPicked(TObjectPtr<AActor> StatComponent)
{
}
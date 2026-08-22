#include "FieldHealthPack.h"
#include "StatComponent.h"


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
    //StatComponent->
}
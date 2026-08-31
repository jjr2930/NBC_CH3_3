#include "ItemBank.h"


// Sets default values
AItemBank::AItemBank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemBank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



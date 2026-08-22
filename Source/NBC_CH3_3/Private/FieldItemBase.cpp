#include "FieldItemBase.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

AFieldItemBase::AFieldItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

    SetRootComponent(SphereCollision);
    StaticMesh->SetupAttachment(SphereCollision);
}

// Called when the game starts or when spawned
void AFieldItemBase::BeginPlay()
{
	Super::BeginPlay();	
}
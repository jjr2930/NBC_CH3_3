#include "FieldItemBase.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "IngameGameMode.h"
#include "JUtility.h"

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

void AFieldItemBase::EndPlay(EEndPlayReason::Type Reason)
{
    if (Reason == EEndPlayReason::Type::Destroyed)
    {
        AIngameGameMode* IngameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
        if (!IsValid(IngameMode))
        {
            JError("Current gamemode is not IngameGameMode type");
            return;
        }

        IngameMode->PickupFieldItem(*this);
    }

    Super::EndPlay(Reason);
}

void AFieldItemBase::SetData(FFieldItemSpawnRow* DataTableRow)
{
    this->Row = DataTableRow;
}


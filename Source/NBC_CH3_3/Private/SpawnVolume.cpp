#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
    SetRootComponent(BoxVolume);
}

FVector ASpawnVolume::GetRandomPositionInVolume()
{
    FBox LocaBox = BoxVolume->CalcLocalBounds().GetBox();
    FVector RandomPointInBox = FMath::RandPointInBox(LocaBox);
    FVector RandomWorldPosition = BoxVolume->GetComponentTransform().TransformPosition(RandomPointInBox);

    FHitResult HitResult;
    FVector Start = RandomWorldPosition + FVector::UpVector * 100.0f;
    FVector End = RandomWorldPosition + FVector::UpVector * -1000.0f;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic))
    {
        return HitResult.ImpactPoint;
    }
    else
    {
        return RandomWorldPosition;
    }
}

void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();

    Spawn();
    LastSpawnTime = (float)(GetWorld()->GetTimeSeconds());
}

void ASpawnVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    double Now = (float)(GetWorld()->GetTimeSeconds());
    if (Now - LastSpawnTime >= SpawnDelay)
    {
        Spawn();
        LastSpawnTime = Now;
    }
}

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

    return RandomWorldPosition;
}


void ASpawnVolume::Tick(float DeltaTime)
{
    double Now = (float)(GetWorld()->GetTimeSeconds());
    if (Now - LastSpawnTime >= SpawnDelay)
    {
        Spawn();
        LastSpawnTime = Now;
    }
}

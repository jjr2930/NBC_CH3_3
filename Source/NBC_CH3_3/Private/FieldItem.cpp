#include "FieldItem.h"
#include "IngameGameMode.h"
#include "JUtility.h"
#include "FieldItemSpawnRow.h"

#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

AFieldItem::AFieldItem()
{
	PrimaryActorTick.bCanEverTick = true;

    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

    SetRootComponent(SphereCollision);
    StaticMesh->SetupAttachment(SphereCollision);
}

// Called when the game starts or when spawned
void AFieldItem::BeginPlay()
{
	Super::BeginPlay();	
}

void AFieldItem::EndPlay(EEndPlayReason::Type Reason)
{
    if (Reason == EEndPlayReason::Type::Destroyed)
    {
        AIngameGameMode* IngameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
        if (!IsValid(IngameMode))
        {
            JError("Current gamemode is not IngameGameMode type");
            return;
        }
    }

    Super::EndPlay(Reason);
}

FFieldItemSpawnRow* AFieldItem::Roll() const
{
    JASSERT_NULLPTR(IsValid(FieldItemTable), "Table is not set");

    //roll item drop table!
    TArray<FFieldItemSpawnRow*> SpawnRows;
    FieldItemTable->GetAllRows<FFieldItemSpawnRow>(FString(TEXT("Field Item Spawn Volume")), SpawnRows);
    checkf(SpawnRows.Num() > 0, TEXT("Empty DataTable"));

    float TotalRate = 0;
    for (auto it : SpawnRows)
    {
        TotalRate += it->GetDropRate();
    }

    float RandomRate = FMath::FRandRange(0.0f, TotalRate);
    float Elapsed = 0.0f;
    TSubclassOf<AFieldItem> FoundFieldItemClass = nullptr;
    FFieldItemSpawnRow* FoundRow = nullptr;
    for (auto It : SpawnRows)
    {
        if (Elapsed <= RandomRate && RandomRate < Elapsed + It->GetDropRate())
        {
            FoundRow = It;
            break;
        }
        else
        {
            Elapsed += It->GetDropRate();
        }
    }

    return FoundRow;
}

FVector AFieldItem::GetStaticMeshWorldSize()
{
    return StaticMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();
}

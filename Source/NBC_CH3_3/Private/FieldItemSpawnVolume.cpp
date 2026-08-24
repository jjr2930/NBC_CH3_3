#include "FieldItemSpawnVolume.h"
#include "FieldItemSpawnRow.h"
#include "JUtility.h"
#include "FieldItemBase.h"

AFieldItemSpawnVolume::AFieldItemSpawnVolume()
{

}

AActor* AFieldItemSpawnVolume::Spawn()
{
    TArray<FFieldItemSpawnRow*> SpawnRows;
    DataTable->GetAllRows<FFieldItemSpawnRow>(FString(TEXT("Field Item Spawn Volume")), SpawnRows);

    if (0 == SpawnRows.Num())
    {
        JError("Spawn rows length is zero");
        return nullptr;
    }

    float TotalRate = 0;
    for (auto it : SpawnRows)
    {
        TotalRate += it->DropRate;
    }

    float RandomRate = FMath::FRandRange(0.0f, TotalRate);
    float Elapsed = 0.0f;
    TSubclassOf<AFieldItemBase> FoundFieldItemClass = nullptr;
    FFieldItemSpawnRow* FoundRow = nullptr;
    for (auto It : SpawnRows)
    {
        if (Elapsed <= RandomRate && RandomRate < Elapsed + It->DropRate)
        {
            FoundFieldItemClass = It->FieldItemActorClass;
            FoundRow = It;
            break;
        }
        else
        {
            Elapsed += It->DropRate;
        }
    }

    if (!IsValid(FoundFieldItemClass))
    {
        JError("Can not found fieldItem");
        return nullptr;
    }

    FVector RandomPosition = GetRandomPositionInVolume();
    AActor* SpawnedActor = GetWorld()->SpawnActor(FoundFieldItemClass, &RandomPosition);

    AFieldItemBase* FieldItemBase = Cast<AFieldItemBase>(SpawnedActor);
    if (!IsValid(FieldItemBase))
    {
        JError("Spawned actor is not field itembase");
        return nullptr;
    }

    FieldItemBase->SetData(FoundRow);

    return SpawnedActor;
}

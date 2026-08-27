#include "FieldItemSpawnVolume.h"
#include "FieldItemSpawnRow.h"
#include "JUtility.h"
#include "FieldItem.h"
#include "Kismet/GameplayStatics.h"

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
        TotalRate += it->GetDropRate();
    }

    float RandomRate = FMath::FRandRange(0.0f, TotalRate);
    float Elapsed = 0.0f;
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

    checkf(IsValid(FieldItem), TEXT("Field Item is nullptr"));
    
    FVector RandomPosition = GetRandomPositionInVolume();
    FRotator SpawnRotator(0.0, 0.0, 0.0);
    FTransform SpawnTransform(SpawnRotator, RandomPosition, FVector::One());
    AFieldItem* SpawnedActor 
        = GetWorld()->SpawnActor<AFieldItem>(FieldItem, SpawnTransform);

    return SpawnedActor;
}
#include "FieldItemSpawnVolume.h"
#include "FieldItemSpawnRow.h"
#include "JUtility.h"
#include "FieldItemBase.h"
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
    FRotator SpawnRotator(0.0, 0.0, 0.0);
    FTransform SpawnTransform(SpawnRotator, RandomPosition, FVector::One());
    AFieldItemBase* SpawnedActor 
        = GetWorld()->SpawnActorDeferred<AFieldItemBase>(FoundFieldItemClass, SpawnTransform);

    checkf(IsValid(SpawnedActor), TEXT("AFieldItemBase is nullptr"));

    SpawnedActor->SetData(FoundRow);
    AActor* Temp = UGameplayStatics::FinishSpawningActor(SpawnedActor, SpawnTransform);
    SpawnedActor = Cast<AFieldItemBase>(Temp);
    checkf(IsValid(SpawnedActor), TEXT("%s is not FieldItembase"), *Temp->GetName());

    return SpawnedActor;
}
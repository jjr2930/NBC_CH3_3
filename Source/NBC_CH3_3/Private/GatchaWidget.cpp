#include "GatchaWidget.h"
#include "FieldItemSpawnRow.h"

void UGatchaWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Super::OnVisibilityChanged.AddDynamic(this, &UGatchaWidget::HandleVisibilityChanged);
}

void UGatchaWidget::HandleVisibilityChanged(ESlateVisibility InVisibility)
{
    //roll item drop table!
    TArray<FFieldItemSpawnRow*> SpawnRows;
    ItemDropTable->GetAllRows<FFieldItemSpawnRow>(FString(TEXT("Field Item Spawn Volume")), SpawnRows);
    checkf(SpawnRows.Num() > 0, TEXT("Empty DataTable"));

    float TotalRate = 0;
    for (auto it : SpawnRows)
    {
        TotalRate += it->DropRate;
    }

    float RandomRate = FMath::FRandRange(0.0f, TotalRate);
    float Elapsed = 0.0f;
    TSubclassOf<AFieldItem> FoundFieldItemClass = nullptr;
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

    //DO SOMETHING
}
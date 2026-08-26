#pragma once

#include "SpawnVolume.h"
#include "CoreMinimal.h"
#include "FieldItemSpawnVolume.generated.h"

class AFieldItem;

UCLASS()
class NBC_CH3_3_API AFieldItemSpawnVolume : public ASpawnVolume
{
    GENERATED_BODY()

public:
    AFieldItemSpawnVolume();

    virtual AActor* Spawn() override;

    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FieldItemSpawnVolume")
    TObjectPtr<UDataTable> DataTable;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FieldItemSpawnVolume")
    TObjectPtr<AFieldItem> FieldItem;
};

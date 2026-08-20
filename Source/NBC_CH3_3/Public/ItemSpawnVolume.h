#pragma once

#include "SpawnVolume.h"
#include "CoreMinimal.h"
#include "ItemSpawnVolume.generated.h"

UCLASS()
class NBC_CH3_3_API AItemSpawnVolume : public ASpawnVolume
{
    GENERATED_BODY()

public:
    AItemSpawnVolume();

    virtual TWeakObjectPtr<AActor> Spawn() override;

private:

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
class UPrimitiveComponent;
struct FHitResult;

UCLASS(Abstract)
class NBC_CH3_3_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();
    FVector GetRandomPositionInVolume();

    UFUNCTION()
    virtual TWeakObjectPtr<AActor> Spawn() PURE_VIRTUAL(ASpawnVolume::Spawn, return nullptr; );
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Spawn Volume| Components")
    TObjectPtr<UBoxComponent> BoxVolume;
};

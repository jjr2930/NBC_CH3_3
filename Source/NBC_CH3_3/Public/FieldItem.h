#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldItem.generated.h"

class USphereComponent;
class UStaticMesshComponent;
class UStatComponent;
struct FFieldItemSpawnRow;

UCLASS()
class NBC_CH3_3_API AFieldItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldItem();
    void SetData(FFieldItemSpawnRow* DataTableRow);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type Reason) override;

    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Field Items|Components")
    TObjectPtr<USphereComponent> SphereCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Field Items|Components")
    TObjectPtr<UStaticMeshComponent> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field Items|Properties")
    TObjectPtr<UDataTable> ItemTables;

    FFieldItemSpawnRow* Row;
};

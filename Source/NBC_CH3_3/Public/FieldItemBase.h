#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldItemBase.generated.h"

class USphereComponent;
class UStaticMesshComponent;
class UStatComponent;
UCLASS()
class NBC_CH3_3_API AFieldItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
    virtual void OnPicked(TObjectPtr<UStatComponent> StatComponent) PURE_VIRTUAL(AFieldItemBase::OnPicked, );
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USphereComponent> SphereCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	
};

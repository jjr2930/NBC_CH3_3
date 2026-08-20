#pragma once

#include "CoreMinimal.h"
#include "FieldItemBase.h"
#include "FieldHealthPack.generated.h"

UCLASS()
class NBC_CH3_3_API AFieldHealthPack : public AFieldItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    virtual void OnPicked(TObjectPtr<UStatComponent> StatComponent) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    int HealingAmount;
};

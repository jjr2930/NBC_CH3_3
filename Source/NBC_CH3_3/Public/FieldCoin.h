#pragma once

#include "FieldItemBase.h"
#include "CoreMinimal.h"
#include "FieldCoin.generated.h"

UCLASS()
class NBC_CH3_3_API AFieldCoin : public AFieldItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldCoin();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


    virtual void OnPicked(TObjectPtr<AActor> Who) override;
};

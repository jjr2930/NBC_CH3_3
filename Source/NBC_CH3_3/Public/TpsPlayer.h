#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TpsPlayer.generated.h"

class UStatComponent;
class UInventoryComponent;
class FInputActionInstance;

UCLASS()
class NBC_CH3_3_API ATpsPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATpsPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    void OnMoveAction(const FInputActionInstance& Value);
    void OnLookAction(const FInputActionInstance& Value);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Components")
    TObjectPtr<UStatComponent> PlayerStat;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Components")
    TObjectPtr<UInventoryComponent> Inventory;


    ///////////////////////////////////////////////////////
    //  Movement
    ///////////////////////////////////////////////////////
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Properties")
    float RotationSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Properties")
    float MoveSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Properties")
    bool InversLookY;
};


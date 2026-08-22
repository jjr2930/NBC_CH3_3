// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TpsPlayer.generated.h"

class UStatComponent;
class UInventoryComponent;

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Components")
    TObjectPtr<UStatComponent> PlayerStat;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Components")
    TObjectPtr<UInventoryComponent> Inventory;


    ///////////////////////////////////////////////////////
    //  Movement
    ///////////////////////////////////////////////////////
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Properties")
    float RotationSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TpsPlayer|Properties")
    float MoveSpeed;
};


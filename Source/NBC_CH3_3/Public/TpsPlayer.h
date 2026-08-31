#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums.h"
#include "TpsPlayer.generated.h"

class UStatComponent;
class UInventoryComponent;
class USpringArmComponent;
class UCameraComponent;
class UGatchaWidget;
class UDataTable;

struct FBuffTableRowBase;
struct FInputActionInstance;

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
    TObjectPtr<UStatComponent> GetStatComponent();


    UFUNCTION()
    void OnComponentBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
    
    UFUNCTION()
    void OnGatchaAnimationFinished();
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Components")
    TObjectPtr<UStatComponent> PlayerStat;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Components")
    TObjectPtr<UInventoryComponent> Inventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Components")
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Components")
    TObjectPtr<UCameraComponent> Camera;


    ///////////////////////////////////////////////////////
    //  Movement
    ///////////////////////////////////////////////////////
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Properties")
    float RotationSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Properties")
    float MoveSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Properties")
    bool InversLookY;


    ///////////////////////////////////////////////////////
    //  Widgets
    ///////////////////////////////////////////////////////
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Widgets")
    TSubclassOf<UGatchaWidget> GatchaWidget;

    ///////////////////////////////////////////////////////
    //  Tables
    ///////////////////////////////////////////////////////
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Tables")
    TObjectPtr<UDataTable> InstantBuffTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "====TpsPlayer====|Tables")
    TObjectPtr<UDataTable> DurationBuffTable;


    ///////////////////////////////////////////////////////
    //  ETC
    ///////////////////////////////////////////////////////
    FString CurrentItemKey;
    EItemType ItemType;

    TObjectPtr<UGatchaWidget> GatchaWidgetInstance;
};


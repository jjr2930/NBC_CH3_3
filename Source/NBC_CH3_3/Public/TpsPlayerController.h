#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "TpsPlayerController.generated.h"

class InputMappingContext;
struct FInputActionInstance;
class UInputAction;
class UInputMappingContext;

UCLASS()
class NBC_CH3_3_API ATpsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    TObjectPtr<UInputAction> GetMoveAction();
    TObjectPtr<UInputAction> GetLookAction();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TpsPlayerController|Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|Input")
    TObjectPtr<UInputAction> LookAction;
};

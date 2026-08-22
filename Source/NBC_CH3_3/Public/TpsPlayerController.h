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

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    void Move(const FInputActionInstance& Value);
    void Look(const FInputActionInstance& Value);
protected:
    TObjectPtr<UInputMappingContext> DefaultMappingContext;
    TObjectPtr<UInputAction> MoveAction;
    TObjectPtr<UInputAction> LookAction;

};

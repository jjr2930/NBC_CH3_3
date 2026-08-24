#include "TpsPlayerController.h"
#include "JUtility.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>
#include <InputAction.h>

void ATpsPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if (!LocalPlayer)
    {   
        JError("There is no local plyaer");
        return;
    }
    
    UEnhancedInputLocalPlayerSubsystem* InputSystem
        = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!InputSystem)
    {
        JError("there is no enhnaced input system");
        return;
    }

    if (!IsValid(DefaultMappingContext))
    {
        JError("Context is Invalid");
        return;
    }

    InputSystem->AddMappingContext(DefaultMappingContext, 0);
}

void ATpsPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
    
    if (nullptr == EnhancedInput)
    {
        JError("EnahcnedInput casting failed");
        return;
    }
}

TObjectPtr<UInputAction> ATpsPlayerController::GetMoveAction()
{
    return MoveAction;
}

TObjectPtr<UInputAction> ATpsPlayerController::GetLookAction()
{
    return LookAction;
}

#include "TpsPlayerController.h"
#include "JUtility.h"

void ATpsPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if (!LocalPlayer)
    {
        JUtility::Error(FString(TEXT("Local Player is null")));
        return;
    }
    
    UEnhancedInputLocalPlayerSubsystem* InputSystem
        = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!InputSystem)
    {
        JUtility::Error(FString(TEXT("Subsystem is nullptr")));
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
        JUtility::Error(FString(TEXT("Input component is not UEnhancedInputComponent")));
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

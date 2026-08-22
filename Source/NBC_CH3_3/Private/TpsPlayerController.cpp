#include "TpsPlayerController.h"

void ATpsPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if (!LocalPlayer)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString(TEXT("Local Player is null")));
        return;
    }
    
    UEnhancedInputLocalPlayerSubsystem* InputSystem
        = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!InputSystem)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString(TEXT("InputSystem is null")));
        return;
    }

    InputSystem->AddMappingContext(DefaultMappingContext, 0);
}

void ATpsPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInput 
        = Cast<UEnhancedInputComponent>(InputComponent))
    {
        Enahce
    }
}

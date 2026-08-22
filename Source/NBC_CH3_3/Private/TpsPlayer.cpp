#include "TpsPlayer.h"
#include "EnhancedInputComponent.h"
#include "TpsPlayerController.h"
#include "JUtility.h"
#include "GameFramework/PawnMovementComponent.h"

ATpsPlayer::ATpsPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATpsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInput
        = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    
    if (nullptr != EnhancedInput)
    {
        JUtility::Error(TEXT("Enhanced inputu is nullptr"));
        return;
    }

    ATpsPlayerController* TpsController 
        = Cast<ATpsPlayerController>(GetController());
    if (nullptr != TpsController)
    {
        JUtility::Error(TEXT("TpsPlayerController casting failed"));
        return;
    }
 
    EnhancedInput->BindAction(
        TpsController->GetMoveAction(),
        ETriggerEvent::Triggered,
        this,
        &ATpsPlayer::OnMoveAction
    );

    EnhancedInput->BindAction(
        TpsController->GetLookAction(),
        ETriggerEvent::Triggered,
        this,
        &ATpsPlayer::OnLookAction
    );
}

void ATpsPlayer::OnMoveAction(const FInputActionInstance& Value)
{
    FVector2D MovingInput = Value.GetValue().Get<FVector2D>();

    FVector Direction = (GetActorForwardVector()) * MovingInput.Y;
    Direction += (GetActorRightVector()) * MovingInput.X;
    Direction.Normalize();

    AddMovementInput(Direction);
}

void ATpsPlayer::OnLookAction(const FInputActionInstance& Value)
{
    FVector2D LookingInput = Value.GetValue().Get<FVector2D>();

    LookingInput.Y = (InversLookY) ? -LookingInput.Y : LookingInput.Y;

    AddControllerPitchInput(LookingInput.Y);
    AddControllerYawInput(LookingInput.X);
}
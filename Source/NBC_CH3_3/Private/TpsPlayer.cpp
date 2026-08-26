#include "TpsPlayer.h"
#include "EnhancedInputComponent.h"
#include "TpsPlayerController.h"
#include "JUtility.h"
#include "GameFramework/PawnMovementComponent.h"
#include "InventoryComponent.h"
#include "StatComponent.h"
#include "GameFramework/Character.h"
#include "FieldItem.h"
#include "GameFramework/SpringArmComponent.h"
#include "IngameGameMode.h"
#include "Components/CapsuleComponent.h"
#include <Camera/CameraComponent.h>
#include <Blueprint/UserWidget.h>

ATpsPlayer::ATpsPlayer()
{
    PlayerStat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
    Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArm->SetupAttachment(GetCapsuleComponent());
    Camera->SetupAttachment(SpringArm);

    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATpsPlayer::OnComponentBeginOverlap);

	PrimaryActorTick.bCanEverTick = true;
}

void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();

    checkf(IsValid(GatchaWidget), TEXT("GatchaWidget is invalid"));

    GatchaWidgetInstance = CreateWidget<UUserWidget>(GatchaWidget);
    GatchaWidget->AddToViewport(1);
    GatchaWidget->SetVisibility(ESlateVisibility::Hidden);	
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
    
    if (!IsValid(EnhancedInput))
    {
        JError("Enhanced inputu is nullptr");
        return;
    }

    ATpsPlayerController* TpsController 
        = Cast<ATpsPlayerController>(GetController());
    if (!IsValid( TpsController))
    {
        JError("TpsPlayerController casting failed");
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

void ATpsPlayer::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent
    , AActor* OtherActor
    , UPrimitiveComponent* OtherComp
    , int32 OtherBodyIndex
    , bool bFromSweep
    , const FHitResult& SweepResult)
{
    AFieldItem* FieldItem = Cast<AFieldItem>(OtherActor);
    if (!IsValid(FieldItem))
    {
        return;
    }

    GatchaWidget->SetVisibility(ESlateVisibility::Visible);

    AIngameGameMode* GameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
    checkf(IsValid(GameMode), TEXT("Current game mode is not AIngameGameMode"));

    GameMode->PickupFieldItem(*FieldItem);
}

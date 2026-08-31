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
#include "GatchaWidget.h"
#include "FieldItemSpawnRow.h"
#include "DurationBuffTableRow.h"
#include "BuffTableRowBase.h"
#include "InstantBuffTableRow.h"

#include "Components/CapsuleComponent.h"
#include <Camera/CameraComponent.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

ATpsPlayer::ATpsPlayer()
    : CurrentItemBuff(nullptr)
    , GatchaWidgetInstance(nullptr)
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

    GatchaWidgetInstance = CreateWidget<UGatchaWidget>(GetWorld(), GatchaWidget);
    GatchaWidgetInstance->AddToViewport(1);
    GatchaWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

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

TObjectPtr<UStatComponent> ATpsPlayer::GetStatComponent()
{
    return PlayerStat;
}

void ATpsPlayer::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent
    , AActor* OtherActor
    , UPrimitiveComponent* OtherComp
    , int32 OtherBodyIndex
    , bool bFromSweep
    , const FHitResult& SweepResult)
{
    JASSERT(IsValid(InstantBuffTable), "InstantBuffTable is invalid or notset");
    JASSERT(IsValid(DurationBuffTable), "DurationBuffTable is invalid or notset");

    AFieldItem* FieldItem = Cast<AFieldItem>(OtherActor);
    JASSERT(IsValid(FieldItem), "%s is not FieldItem", *OtherActor->GetName());

    AIngameGameMode* GameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
    JASSERT(IsValid(GameMode), "Current game mode is not AIngameGameMode");

    FFieldItemSpawnRow* ItemRow = FieldItem->Roll();

    switch (ItemRow->GetBuffType())
    {
    case EBuffType::Duration:
        CurrentItemBuff = DurationBuffTable->FindRow<FDurationBuffTableRow>(ItemRow->GetTableKey(), "Buff finding");
        break;

    case EBuffType::Instant:
        CurrentItemBuff = InstantBuffTable->FindRow<FInstantBuffTableRow>(ItemRow->GetTableKey(), "Buff Finding");
        break;
    }

    UGatchaWidget::FGatchaAnimationFinishedEvent AnimationFinishedCallback;
    AnimationFinishedCallback.BindDynamic(this, &ATpsPlayer::OnGatchaAnimationFinished);

    GatchaWidgetInstance->SetItemType(ItemRow->GetItemType());
    GatchaWidgetInstance->SetVisibility(ESlateVisibility::Visible);
    GatchaWidgetInstance->PlayAnimation(AnimationFinishedCallback);

    GetWorld()->DestroyActor(FieldItem);

    Inventory->GetOwner()
}

void ATpsPlayer::OnGatchaAnimationFinished()
{
    AIngameGameMode* GameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());

    PlayerStat->AddBuff(CurrentItemBuff->ToBuff());
}

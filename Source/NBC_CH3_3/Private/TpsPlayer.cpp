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
#include "QuestItemTableRow.h"
#include "ConsumeItemTableRow.h"
#include "BuffFactory.h"
#include "IngameState.h"

#include "Components/CapsuleComponent.h"
#include <Camera/CameraComponent.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

ATpsPlayer::ATpsPlayer()
    : GatchaWidgetInstance(nullptr)
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

void ATpsPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    PlayerStat->GetDelegateIntStatClamp()->Unbind();

    Super::EndPlay(EndPlayReason);
}

void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();

    JASSERT(IsValid(GatchaWidget), "GatchaWidget is invalid");

    PlayerStat->GetDelegateIntStatClamp()->BindUObject(this, &ATpsPlayer::ClampIntStat);
    PlayerStat->GetIntCallbacks()->AddUObject(this, &ATpsPlayer::OnStatChanged);

    TObjectPtr<AIngameState> IngameState
        = Cast<AIngameState>(GetWorld()->GetGameState());

    JASSERT(IsValid(IngameState), "Current state is not IngameState");

    IngameState->OnWaveIndexChanged.AddUObject(this, &ATpsPlayer::OnWaveIndexChanged);

    GatchaWidgetInstance = CreateWidget<UGatchaWidget>(GetWorld(), GatchaWidget);
    GatchaWidgetInstance->AddToViewport(1);
    GatchaWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
}

void ATpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //TODO: Tick에서 하지 않는 더 좋은 방법을 찾아보자.

    JASSERT(PlayerStat->HasStat(ECharacterStatType::MovingSpeed, false), "There is not Moving Speed Stat");
    
    float BuffedMovingSpeed = PlayerStat->GetFloat(ECharacterStatType::MovingSpeed);

    GetCharacterMovement()->MaxWalkSpeed = BuffedMovingSpeed;
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

    FFieldItemSpawnRow* FieldItemTableRow = FieldItem->Roll();
    CurrentItemKey = FieldItemTableRow->GetTableKey();
    CurrentItemType = FieldItemTableRow->GetItemType();
    CurrentAmount = FieldItemTableRow->RollAmount();

    UGatchaWidget::FGatchaAnimationFinishedEvent AnimationFinishedCallback;
    AnimationFinishedCallback.BindDynamic(this, &ATpsPlayer::OnGatchaAnimationFinished);

    GatchaWidgetInstance->SetIcon(FieldItemTableRow->GetIconTexture());
    GatchaWidgetInstance->SetVisibility(ESlateVisibility::Visible);
    GatchaWidgetInstance->PlayAnimation(AnimationFinishedCallback);

    GetWorld()->DestroyActor(FieldItem);
}

void ATpsPlayer::OnGatchaAnimationFinished()
{
    AIngameGameMode* GameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
    switch (CurrentItemType)
    {
    case EItemType::QuestItem:
    {
        FQuestItemTableRow* QuestItemRow = QuestItemTable->FindRow<FQuestItemTableRow>(CurrentItemKey, TEXT("TPS Player"));
        JASSERT((nullptr != QuestItemRow), "Item row is not quest item row");

        Inventory->AddItem(CurrentItemType, CurrentItemKey, CurrentAmount);

        JLog("%s %d added", *QuestItemRow->ItemDisplayName, CurrentAmount);
        break;
    }
    case EItemType::ConsumeItem:
    {
        FConsumeItemTableRow* ConsumeItemRow = ConsumeItemTable->FindRow<FConsumeItemTableRow>(CurrentItemKey, TEXT("Tps Player"));

        JASSERT((nullptr != ConsumeItemRow), "Itemr ow is not consumeitem row");

        FBuff* NewBuff = nullptr;
        FBuffTableRowBase* BuffTableRow = nullptr;
        switch (ConsumeItemRow->BuffType)
        {
        case EBuffType::Duration:
        {
            //TODO BuffBank 라는 테이블들에서 검색해서 찾아주는 클래스를 만들면 좀 더 추상화 할 수 있다.
            BuffTableRow = static_cast<FBuffTableRowBase*>(DurationBuffTable->FindRow<FDurationBuffTableRow>(ConsumeItemRow->BuffRowName, TEXT("TpsPlayer")));

            NewBuff = FBuffFactory::CreateBuff(GetWorld(), ConsumeItemRow->BuffType, BuffTableRow);
            break;
        }

        case EBuffType::Instant:
        {
            BuffTableRow = static_cast<FInstantBuffTableRow*>(InstantBuffTable->FindRow<FInstantBuffTableRow>(ConsumeItemRow->BuffRowName, TEXT("TpsPlayer")));

            NewBuff = FBuffFactory::CreateBuff(GetWorld(), ConsumeItemRow->BuffType, BuffTableRow);
            break;
        }
        }

        PlayerStat->AddBuff(NewBuff);
        break;
    }

    default:
        break;
    }
}

void ATpsPlayer::ClampIntStat(ECharacterStatType InStatType)
{
    JASSERT(PlayerStat->HasStat(InStatType, true)
        , "%s stat not exist"
        , *GET_ENUM_STRING(ECharacterStatType, InStatType));

    switch (InStatType)
    {
    case ECharacterStatType::Health:
    {
        int CurrentHealth = PlayerStat->GetInt(ECharacterStatType::Health);
        int MaxHealth = PlayerStat->GetInt(ECharacterStatType::MaxHealth);

        if (CurrentHealth > MaxHealth)
            CurrentHealth = MaxHealth;
        else if (CurrentHealth <= 0)
            CurrentHealth = 0;

        PlayerStat->SetOrInsertWithoutNotify(ECharacterStatType::Health, CurrentHealth);
        break;
    }
    default:
        break;
    }
}

void ATpsPlayer::OnStatChanged(ECharacterStatType InStatType, int InValue)
{
    switch (InStatType)
    {
    case ECharacterStatType::Health:
    {
        if (InValue <= 0)
        {
            AIngameGameMode* IngameGameMode = Cast<AIngameGameMode>(GetWorld()->GetAuthGameMode());
            JASSERT(IsValid(IngameGameMode), "Current Game mode is not ingamegamemode");

            IngameGameMode->OnPlayerDead();
        }
        break;
    }
    default:
        break;
    }
}

void ATpsPlayer::OnWaveIndexChanged(int CurrentWaveIndex, int TotalWaveCount)
{
    Inventory->Clear
}

#include "TpsPlayerController.h"
#include "JUtility.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget.h"
#include "PlayerStatWidget.h"
#include "StatComponent.h"
#include "TpsPlayer.h"

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

    if (!IngameWidget)
    {
        JError("Widget is invalid");
        return;
    }

    TObjectPtr<UIngameWidget> WidgetInstance = CreateWidget<UIngameWidget>(GetWorld(), IngameWidget);
    WidgetInstance->AddToViewport(0);
    JASSERT(IsValid(StatWidget), "Player stat widget is inavlid");

    TObjectPtr<UPlayerStatWidget> StatWidgetInstance = CreateWidget<UPlayerStatWidget>(GetWorld(), StatWidget);
    StatWidgetInstance->AddToViewport(0);

    ATpsPlayer* TpsPlayer = Cast<ATpsPlayer>(GetPawn());
    JASSERT(IsValid(TpsPlayer), "Player is not ATpsPlayer");
    
    TObjectPtr<UStatComponent> StatComponent = TpsPlayer->GetStatComponent();
    JASSERT(IsValid(StatComponent), "Player does not have StatComponent");

    StatWidgetInstance->SetStatComponent(StatComponent);
    
    FInputModeGameOnly GameOnly;
    SetInputMode(GameOnly);
    SetShowMouseCursor(false);
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

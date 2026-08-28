#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TpsPlayerController.generated.h"

class InputMappingContext;
struct FInputActionInstance;
class UInputAction;
class UInputMappingContext;
class UIngameWidget;
class UPlayerStatWidget;

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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|Input")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|UI")
    TSubclassOf<UIngameWidget> IngameWidget;

    //TODO: IngameWidget 안에 넣는게 맞지 않을까?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TpsPlayerController|UI")
    TSubclassOf<UPlayerStatWidget> StatWidget;
};

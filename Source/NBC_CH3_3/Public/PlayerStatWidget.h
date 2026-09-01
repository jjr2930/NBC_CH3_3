// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatComponent.h"
#include "Buff.h"
#include "PlayerStatWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UStatComponent;
class UVerticalBox;
class UScrollBox;
class UBuffProgressBar;


UCLASS()
class NBC_CH3_3_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetStatComponent(TObjectPtr<UStatComponent> InStatComponent);

    UFUNCTION()
    void OnStatChanged(ECharacterStatType InStatType, int Value);

    void OnBuffAdded(FBuff* NewBuff);
    void OnBuffRemoved(FBuff* OldBuff);

protected: 
    void RefreshHealthUi();
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> HealthProgressBar;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> HealthProgressBarText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UScrollBox> BuffScrollBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "=== Player State Widget ===|References")
    TSubclassOf<UBuffProgressBar> BuffProbressBarClass;

    UPROPERTY()
    TArray<UBuffProgressBar*> CreatedBuffProgressbars;

    UPROPERTY() 
    TObjectPtr<UStatComponent> TargetStatComponent;

};

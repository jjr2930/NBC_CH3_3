#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums.h"
#include "StatComponent.generated.h"

class FBuff;

UCLASS( )
class NBC_CH3_3_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnIntStatChangedEvent, ECharacterStatType, int);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFloatStatChangedEvent, ECharacterStatType, float);

public:	
	// Sets default values for this component's properties
	UStatComponent();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetOrInsert(ECharacterStatType statType, int value);
    void SetOrInsert(ECharacterStatType statType, float value);
    int GetInt(ECharacterStatType statType, int defaultValue = 0);
    float GetFloat(ECharacterStatType statType, float defaultValue = 0);
    bool HasStat(ECharacterStatType InStatType, bool IsInt);

    void AddBuff(FBuff* Buff);
    
    FOnIntStatChangedEvent* GetIntCallbacks();
    FOnFloatStatChangedEvent* GetFloatCallback();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    TMap<ECharacterStatType, int> IntStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    TMap<ECharacterStatType, float> FloatStats;

    TArray<FBuff*> Buffs;

    FOnIntStatChangedEvent OnIntStatChangedCallbacks;
    FOnFloatStatChangedEvent OnFloatStatChangedCallbacks;
};

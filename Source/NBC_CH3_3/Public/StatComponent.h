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
    /// <summary>
    /// TODO: 좀 더 적절한 이름을 찾을것
    /// </summary>
    DECLARE_DELEGATE_OneParam(FIntStatClampCallback, ECharacterStatType);
    DECLARE_DELEGATE_OneParam(FFloatStatClampCallback, ECharacterStatType);

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffAddedEvent, FBuff*);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffRemovedEvent, FBuff*);

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnIntStatChangedEvent, ECharacterStatType, int);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFloatStatChangedEvent, ECharacterStatType, float);

public:	
	// Sets default values for this component's properties
	UStatComponent();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetOrInsert(ECharacterStatType statType, int value);
    void SetOrInsert(ECharacterStatType statType, float value);
    void SetOrInsertWithoutNotify(ECharacterStatType InStatType, int Value);
    void SetOrInsertWithoutNotify(ECharacterStatType InStatType, float Value);
    /// <summary>
    /// remove default value, this function can be causing wired logic
    /// </summary>
    /// <param name="statType"></param>
    /// <param name="defaultValue"></param>
    /// <returns></returns>
    int GetInt(ECharacterStatType statType, int defaultValue = 0);
    /// <summary>
    /// remove default value, this function can be causing wired logic
    /// </summary>
    /// <param name="statType"></param>
    /// <param name="defaultValue"></param>
    /// <returns></returns>
    float GetFloat(ECharacterStatType statType, float defaultValue = 0);
    bool HasStat(ECharacterStatType InStatType, bool IsInt);

    void AddBuff(FBuff* Buff);
    /// <summary>
    /// TOODO: change name to like GetIntStatCallbackDelegate
    /// </summary>
    /// <returns></returns>
    FOnIntStatChangedEvent* GetIntCallbacks();
    /// <summary>
    /// TODO: Change name to like GetIntStatCallbackDelegate 
    /// </summary>
    /// <returns></returns>
    FOnFloatStatChangedEvent* GetFloatCallback();
    FIntStatClampCallback* GetDelegateIntStatClamp();
    FFloatStatClampCallback* GetDelegateFloatStatClamp();
    FOnBuffAddedEvent* GetDelegateBuffAdded();
    FOnBuffRemovedEvent* GetDelegateBuffRemoved();

    const TArray<FBuff*>* GetBuffs();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    TMap<ECharacterStatType, int> IntStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    TMap<ECharacterStatType, float> FloatStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
    TMap<ECharacterStatType, ECharacterStatType> ClampStat;

    TArray<FBuff*> Buffs;

    FOnIntStatChangedEvent OnIntStatChangedCallbacks;
    FOnFloatStatChangedEvent OnFloatStatChangedCallbacks;
    FIntStatClampCallback IntStatClampCallback;
    FFloatStatClampCallback FloatStatClampCallback;

    FOnBuffAddedEvent BuffAddedCallbacks;
    FOnBuffRemovedEvent BuffRemovedCallbacks;
};

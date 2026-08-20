

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
    Health      UMETA(DisplayName = "Health"),
    MaxHealth   UMETA(DisplayName = "Max Health")
};

UCLASS( )
class NBC_CH3_3_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetOrAdd(ECharacterStatType statType, int value);
    void SetOrAdd(ECharacterStatType statType, float value);
    int GetInt(ECharacterStatType statType, int defaultValue);
    float GetFloat(ECharacterStatType statType, float defaultValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats")
    TMap<ECharacterStatType, int> IntStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stats")
    TMap<ECharacterStatType, float> FloatStats;
};

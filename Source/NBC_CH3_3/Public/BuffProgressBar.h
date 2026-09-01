#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffProgressBar.generated.h"

class UProgressBar;
class UTexture2D;
class UImage;
class FDurationBuff;

UCLASS()
class NBC_CH3_3_API UBuffProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
    void BindBuff(FDurationBuff* Buff);
    bool IsMyBuff(FDurationBuff* Buff);
    void SetPercent(float Percent);
    void SetTexture(UTexture2D* IconTexture);

protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> RemainTimeProgressBar;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Icon;
    
    /*
    * TODO: 스마트 포인터로 변환하기
    */
    FDurationBuff* DurationBuff;
};

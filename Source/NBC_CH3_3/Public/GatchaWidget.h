#pragma once

#include <Blueprint/UserWidget.h>
#include "CoreMinimal.h"
#include "GatchaWidget.generated.h"

class UDataTable;

UCLASS()
class NBC_CH3_3_API UGatchaWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GatchWidget|Properties")
    TObjectPtr<UDataTable> ItemDropTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GatchWidget|Properties")
    TObjectPtr<UDataTable> ItemTable;

    UFUNCTION()
    void HandleVisibilityChanged(ESlateVisibility InVisibility);
};

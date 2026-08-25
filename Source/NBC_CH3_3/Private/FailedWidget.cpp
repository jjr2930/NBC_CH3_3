#include "FailedWidget.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UFailedWidget::NativeOnInitialized()
{
    Button->OnClicked.AddDynamic(this, &UFailedWidget::OnClicked);
}

void UFailedWidget::OnClicked()
{
    checkf(!MenuLevel.IsNull(), TEXT("MenuLevel is no set"));

    UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
}
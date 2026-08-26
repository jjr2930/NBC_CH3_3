#include "GatchaWidget.h"
#include "FieldItemSpawnRow.h"

void UGatchaWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Super::OnVisibilityChanged.AddDynamic(this, &UGatchaWidget::HandleVisibilityChanged);
}

void UGatchaWidget::HandleVisibilityChanged(ESlateVisibility InVisibility)
{
    

     //
}
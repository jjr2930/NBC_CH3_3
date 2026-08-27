#include "PlayerStatWidget.h"
#include "StatComponent.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>


void UPlayerStatWidget::SetStatComponent(TObjectPtr<UStatComponent> InStatComponent)
{
    TargetStatComponent = InStatComponent;

    TargetStatComponent
        ->GetIntCallbacks()
        ->AddUObject(this, &UPlayerStatWidget::OnStatChanged);
}

void UPlayerStatWidget::OnStatChanged(ECharacterStatType InStatType, int Value)
{
    switch (InStatType)
    {

    case ECharacterStatType::Health :
    {
        RefreshHealthUi();
        break;
    }
    
    case ECharacterStatType::MaxHealth:
    {
        RefreshHealthUi();
        break;
    }

    default:
        break;
    }
}

void UPlayerStatWidget::RefreshHealthUi()
{
    int MaxHealth = TargetStatComponent->GetInt(ECharacterStatType::Health);
    int CurrentHealth = TargetStatComponent->GetInt(ECharacterStatType::MaxHealth);
    float Percent = (float(CurrentHealth) / (float)MaxHealth);

    HealthProgressBar->SetPercent(Percent);

    FText HealthText = FText::Format(
        FText::FromString(TEXT("{0}/{1}"))
        , CurrentHealth
        , MaxHealth
    );

    HealthProgressBarText->SetText(HealthText);
}
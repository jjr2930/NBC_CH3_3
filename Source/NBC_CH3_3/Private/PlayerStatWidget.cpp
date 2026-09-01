#include "PlayerStatWidget.h"
#include "StatComponent.h"
#include "BuffProgressBar.h"
#include "Buff.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Components/ScrollBox.h>

void UPlayerStatWidget::SetStatComponent(TObjectPtr<UStatComponent> InStatComponent)
{
    TargetStatComponent = InStatComponent;

    TargetStatComponent
        ->GetIntCallbacks()
        ->AddUObject(this, &UPlayerStatWidget::OnStatChanged);

    TargetStatComponent
        ->GetDelegateBuffAdded()
        ->AddUObject(this, &UPlayerStatWidget::OnBuffAdded);

    TargetStatComponent
        ->GetDelegateBuffRemoved()
        ->AddUObject(this, &UPlayerStatWidget::OnBuffRemoved);

    RefreshHealthUi();
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

void UPlayerStatWidget::OnBuffAdded(FBuff* NewBuff)
{
    if (NewBuff->GetBuffType() != EBuffType::Duration)
        return;

    FDurationBuff* DurationBuff = static_cast<FDurationBuff*>(NewBuff);

    UBuffProgressBar* NewBuffProgressBar = CreateWidget<UBuffProgressBar>(this, BuffProbressBarClass);
    NewBuffProgressBar->BindBuff(DurationBuff);
    CreatedBuffProgressbars.Emplace(NewBuffProgressBar);

    BuffScrollBox->AddChild(NewBuffProgressBar);
}

void UPlayerStatWidget::OnBuffRemoved(FBuff* OldBuff)
{
    if (OldBuff->GetBuffType() != EBuffType::Duration)
        return;

    FDurationBuff* DurationBuff = static_cast<FDurationBuff*>(OldBuff);
    int Count = CreatedBuffProgressbars.Num();
    for (int i = Count - 1; i >= 0; --i)
    {
        UBuffProgressBar* ProgressBar = CreatedBuffProgressbars[i];
        if (ProgressBar->IsMyBuff(DurationBuff))
        {
            CreatedBuffProgressbars.RemoveAt(i);
            ProgressBar->RemoveFromParent();
            
            JLog("Buff Progress bar removed");
            break;
        }
    }
}

void UPlayerStatWidget::RefreshHealthUi()
{
    int CurrentHealth = TargetStatComponent->GetInt(ECharacterStatType::Health);
    int MaxHealth = TargetStatComponent->GetInt(ECharacterStatType::MaxHealth);
    float Percent = (float(CurrentHealth) / (float)MaxHealth);

    HealthProgressBar->SetPercent(Percent);

    FText HealthText = FText::Format(
        FText::FromString(TEXT("{0}/{1}"))
        , CurrentHealth
        , MaxHealth
    );

    HealthProgressBarText->SetText(HealthText);
}
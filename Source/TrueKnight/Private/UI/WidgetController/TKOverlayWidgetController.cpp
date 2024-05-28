// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/TKOverlayWidgetController.h"

#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"

void UTKOverlayWidgetController::BroadcastInitialValues()
{
	const UTKAttributeSet* TKAttributeSet = CastChecked<UTKAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(TKAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(TKAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(TKAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(TKAttributeSet->GetMaxMana());

	OnStaminaChanged.Broadcast(TKAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(TKAttributeSet->GetMaxStamina());
	
}

void UTKOverlayWidgetController::BindCallbacksToDependencies()
{
	const UTKAttributeSet* TKAttributeSet = CastChecked<UTKAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetHealthAttribute()).AddUObject(this, &UTKOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UTKOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetManaAttribute()).AddUObject(this, &UTKOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UTKOverlayWidgetController::MaxManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetStaminaAttribute()).AddUObject(this, &UTKOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UTKOverlayWidgetController::MaxStaminaChanged);

	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

void UTKOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UTKOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UTKOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UTKOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UTKOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UTKOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}

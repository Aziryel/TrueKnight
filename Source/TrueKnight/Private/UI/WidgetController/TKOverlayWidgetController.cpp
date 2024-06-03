// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/TKOverlayWidgetController.h"

#include "TKGameplayTags.h"
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
	const FTKGameplayTags& GameplayTags = FTKGameplayTags::Get();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TKAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	TKAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	TKAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	TKAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	TKAttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	TKAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this, GameplayTags](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				if (Tag.MatchesTag(GameplayTags.MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

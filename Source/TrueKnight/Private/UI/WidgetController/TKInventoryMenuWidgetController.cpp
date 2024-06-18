// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/TKInventoryMenuWidgetController.h"

#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/Data/InventoryInfo.h"

void UTKInventoryMenuWidgetController::BindCallbacksToDependencies()
{
	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->OnInventoryUpdated.AddLambda(
		[this](const FGameplayTag& ItemTag, const int32 Quantity, const bool bCreateWidget)
		{
			FTKInventoryInfo Info = InventoryInfoDataAsset->FindInventoryInfoForTag(ItemTag);
			Info.ItemQuantity = Quantity;
			ItemInfoDelegate.Broadcast(Info, bCreateWidget);
		}
	);
}

void UTKInventoryMenuWidgetController::BroadcastInitialValues()
{
	for (const TTuple<FGameplayTag, FActiveGameplayEffectHandle> Pair : Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->InventoryMap)
	{
		// Get the GameplayTag and the associated GameplayEffectHandle
		// We use local variables to simplify the readability
		FGameplayTag GameplayTag = Pair.Key;
		const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = Pair.Value;

		// Retrieve the ActiveGameplayEffect from the handle to have access to the stack number (the item amount held by the player)

		if (const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveGameplayEffectHandle))
		{
			// Get the number of stacks
			const int32 NumStacks = ActiveEffect->Spec.GetStackCount();

			// Log or use the stack count (only for debug purposes)
			UE_LOG(LogTemp, Warning, TEXT("Tag: %s, Stacks: %d"), *GameplayTag.ToString(), NumStacks);

			// We only create a new widget for each item if the stack count is higher than 0.
			// This should always be the case because there shouldn't be an item with 0 stacks, but it's better to double-check
			if (NumStacks > 0)
			{
				FTKInventoryInfo Info = InventoryInfoDataAsset->FindInventoryInfoForTag(GameplayTag);
				Info.ItemQuantity = NumStacks;
				// This is the only moment we create a widget for each item
				ItemInfoDelegate.Broadcast(Info, true);
			}
			else
			{
				// We should never be able to reach this point
				UE_LOG(LogTemp, Warning, TEXT("There is an item with 0 stacks in the inventory: %s"), *ActiveGameplayEffectHandle.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No active effect found for handle: %s"), *ActiveGameplayEffectHandle.ToString());
		}
	}
}

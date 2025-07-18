// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/Abilities/TKGameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"


void UTKAbilitySystemComponent::AbilityActorInfoSet()
{
	//This function is called from InitAbilityActorInfo in the Player Character and in the Enemy Character
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UTKAbilitySystemComponent::OnEffectApplied);
}

void UTKAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : StartupAbilities)
	{
		if (!AbilityClass) continue;

		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		// Cast to check if this is a custom ability type
		if (const UTKGameplayAbility* TKAbility = Cast<UTKGameplayAbility>(AbilitySpec.Ability))
		{
			// Add dynamic ability tags
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(TKAbility->StartupInputTag);

			// Give the ability but don't activate it yet
			GiveAbility(AbilitySpec);

			// If the ability needs to activate immediately, trigger it (server-side)
			if (TKAbility->bActivateOnGiven) 
			{
				// Ensure replication and activation happens on clients
				FGameplayAbilitySpecHandle Handle = GiveAbility(AbilitySpec);
				TryActivateAbility(Handle);
                
				UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Activating Ability: %s"), *GetNameSafe(AbilitySpec.Ability)), true, false, FColor::Blue, 5.f);
			}
		}
	}
}

void UTKAbilitySystemComponent::ClientActivateAbilities()
{
	for (auto AbilitySpec : GetActivatableAbilities())
	{
		if (const UTKGameplayAbility* TKAbility = Cast<UTKGameplayAbility>(AbilitySpec.Ability))
		{
			if (TKAbility->bActivateOnGiven)
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UTKAbilitySystemComponent::AddItemToInventory(const FGameplayTag ItemTag,
                                                   FActiveGameplayEffectHandle ActiveEffectHandle, const float Level, const int32 Quantity)
{
	const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(ActiveEffectHandle);
	FGameplayEffectSpecHandle SpecHandle = FGameplayEffectSpecHandle(new FGameplayEffectSpec(ActiveEffect->Spec));
	if (InventoryMap.Contains(ItemTag))
	{
		// Update existing item (e.g., increase stack count)
		// OnInventoryUpdated.Broadcast(ItemTag, SpecHandle.Data->GetStackCount(), false);
	}
	else
	{
		// Create new effect spec and add to the map
		SpecHandle.Data->SetStackCount(Quantity); // Initial stack count
		InventoryMap.Add(ItemTag, ActiveEffectHandle);
		OnGameplayEffectStackChangeDelegate(ActiveEffectHandle)->AddLambda(
		[this, ItemTag](FActiveGameplayEffectHandle ActiveHandle, int32 NewStack, int32 OldStack)
		{
			// We only create a widget (true) when creating the inventory widget
			OnInventoryUpdated.Broadcast(ItemTag, NewStack, false);
		}
		);
		// We only create a widget (true) when creating the inventory widget
		OnInventoryUpdated.Broadcast(ItemTag, SpecHandle.Data->GetStackCount(), false);
	}
}

void UTKAbilitySystemComponent::RemoveItemFromInventory(const FGameplayTag ItemTag, const int32 Quantity)
{
	if (!InventoryMap.Contains(ItemTag))
	{
		return; // Item not found
	}

	FActiveGameplayEffectHandle ActiveEffectHandle = InventoryMap[ItemTag];
	const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(ActiveEffectHandle);
	FGameplayEffectSpecHandle SpecHandle = FGameplayEffectSpecHandle(new FGameplayEffectSpec(ActiveEffect->Spec));
	int32 CurrentStackCount = SpecHandle.Data->GetStackCount();

	if (CurrentStackCount <= Quantity)
	{
		// Remove the item completely
		InventoryMap.Remove(ItemTag);

		// Optionally, remove the gameplay effect from the ASC
		RemoveActiveEffectsWithTags(FGameplayTagContainer(ItemTag));
	}
	else
	{
		// Decrease the stack count
		SpecHandle.Data->SetStackCount(CurrentStackCount - Quantity);
	}

	// Broadcast inventory update
	// We only create a widget (true) when creating the inventory widget
	OnInventoryUpdated.Broadcast(ItemTag, SpecHandle.Data->GetStackCount(), false);
}

FActiveGameplayEffectHandle UTKAbilitySystemComponent::GetItemFromInventory(const FGameplayTag ItemTag) const
{
	// Possibly get the ActiveGameplayEffect instead of the handle?
	
	if (InventoryMap.Contains(ItemTag))
	{
		return InventoryMap[ItemTag];
	}
	return FActiveGameplayEffectHandle();
}

void UTKAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UTKAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UTKAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	const FTKGameplayTags& GameplayTags = FTKGameplayTags::Get();
	
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	if (TagContainer.HasTag(GameplayTags.InventoryTag))
	{
		AddItemToInventory(TagContainer.First(), ActiveEffectHandle, EffectSpec.GetLevel(), EffectSpec.GetStackCount());
	}
	else
	{
		EffectAssetTags.Broadcast(TagContainer);
	}
}


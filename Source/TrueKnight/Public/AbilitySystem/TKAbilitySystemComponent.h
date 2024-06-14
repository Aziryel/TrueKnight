// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TKAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInventoryUpdated, const FGameplayTag& /*ItemTag*/, const int32, const bool);

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	FOnInventoryUpdated OnInventoryUpdated;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddItemToInventory(const FGameplayTag ItemTag, FActiveGameplayEffectHandle ActiveEffectHandle, const float Level, const int32 Quantity);
	UFUNCTION(BlueprintCallable, Category = "GAS|Inventory")
	void RemoveItemFromInventory(const FGameplayTag ItemTag, const int32 Quantity);
	UFUNCTION(BlueprintCallable, Category = "GAS|Inventory")
	FActiveGameplayEffectHandle GetItemFromInventory(const FGameplayTag ItemTag) const;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:

	TMap<FGameplayTag, FActiveGameplayEffectHandle> InventoryMap;
	
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};

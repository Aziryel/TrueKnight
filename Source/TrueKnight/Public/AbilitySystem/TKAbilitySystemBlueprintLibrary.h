// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TKAbilitySystemBlueprintLibrary.generated.h"

/**
 * 
 */

struct FGameplayEffectContextHandle;
class UTKInventoryMenuWidgetController;
class UAbilitySystemComponent;
class UTKAttributeMenuWidgetController;
class UTKOverlayWidgetController;

UCLASS()
class TRUEKNIGHT_API UTKAbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "TKAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UTKOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "TKAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UTKAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "TKAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UTKInventoryMenuWidgetController* GetInventoryMenuWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|Inventory")
	static void AddItemToInventory(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayEffect> GameplayEffectClass, const float Level = 1.f, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|Inventory")
	static void RemoveItemFromInventory(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag ItemTag, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|ClassDefaults", meta = (DefaultToSelf = "WorldContextObject"))
	static void InitializeDefaultsAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|ClassDefaults", meta = (DefaultToSelf = "WorldContextObject"))
	static void GiveStartupAbilitites(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|ClassDefaults", meta = (DefaultToSelf = "WorldContextObject"))
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "TKAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "TKAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category = "TKAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
};

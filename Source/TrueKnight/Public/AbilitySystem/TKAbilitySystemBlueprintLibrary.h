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
};

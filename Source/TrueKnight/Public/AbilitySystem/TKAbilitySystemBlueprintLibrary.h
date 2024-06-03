// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TKAbilitySystemBlueprintLibrary.generated.h"

/**
 * 
 */

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
};

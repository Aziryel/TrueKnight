// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TKWidgetController.h"
#include "TKAttributeMenuWidgetController.generated.h"

/**
 * This is created in TKHUD and then is et directly in the TKAttributeMenu widget blueprint class
 * so the attribute menu hass access to it's own widget controller with the player's information.
 * The class is accessed using the TKAbilitySystemBlueprintLibrary in the widget.
 */

UCLASS(BlueprintType, Blueprintable)
class TRUEKNIGHT_API UTKAttributeMenuWidgetController : public UTKWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	
};

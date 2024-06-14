// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/InventoryInfo.h"
#include "UI/WidgetController/TKWidgetController.h"
#include "TKInventoryMenuWidgetController.generated.h"

struct FTKInventoryInfo;
class UInventoryInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemInfoSignature, FTKInventoryInfo, Info, bool, bCreateWidget);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TRUEKNIGHT_API UTKInventoryMenuWidgetController : public UTKWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Inventory")
	FItemInfoSignature ItemInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InventoryData")
	TObjectPtr<UInventoryInfo> InventoryInfoDataAsset;
	
};

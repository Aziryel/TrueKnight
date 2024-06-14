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
	
}

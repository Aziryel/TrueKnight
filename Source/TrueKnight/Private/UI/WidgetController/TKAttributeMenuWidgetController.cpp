// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/TKAttributeMenuWidgetController.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UTKAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UTKAttributeSet* AS = CastChecked<UTKAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UTKAttributeMenuWidgetController::BroadcastInitialValues()
{
	UTKAttributeSet* AS = CastChecked<UTKAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UTKAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FTKAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

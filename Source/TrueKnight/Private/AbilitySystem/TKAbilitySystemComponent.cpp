// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAbilitySystemComponent.h"

void UTKAbilitySystemComponent::AbilityActorInfoSet()
{
	//This function is called from InitAbilityActorInfo in the Player Character and in the Enemy Character
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UTKAbilitySystemComponent::OnEffectApplied);
}

void UTKAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		//TODO: Broadcast the tag to the widget controller
		const FString Msg = FString::Printf(TEXT("Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, Msg);
	}
}

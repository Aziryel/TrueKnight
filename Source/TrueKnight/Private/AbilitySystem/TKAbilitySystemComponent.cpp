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
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Effect Applied!")));
}

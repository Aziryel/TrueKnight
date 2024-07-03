// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAbilitySystemGlobals.h"

#include "TKAbilityTypes.h"

FGameplayEffectContext* UTKAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FTKGameplayEffectContext();
}

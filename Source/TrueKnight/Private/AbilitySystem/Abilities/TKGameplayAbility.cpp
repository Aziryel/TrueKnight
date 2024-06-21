// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TKGameplayAbility.h"


float UTKGameplayAbility::GetDamageAtAbilityLevel() const
{
	return Damage.GetValueAtLevel(GetAbilityLevel());
}

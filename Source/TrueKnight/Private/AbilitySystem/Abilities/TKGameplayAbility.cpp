// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TKGameplayAbility.h"


FDamageTypeByLevel UTKGameplayAbility::GetDamageAtAbilityLevel() const
{
	FDamageTypeByLevel DamageTypes;
	DamageTypes.TrueDamage = Damage.TrueDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.PhysicalDamage = Damage.PhysicalDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.MagicDamage = Damage.MagicDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.FireDamage = Damage.FireDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.ColdDamage = Damage.ColdDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.LightningDamage = Damage.LightningDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.PoisonDamage = Damage.PoisonDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.HolyDamage = Damage.HolyDamage.GetValueAtLevel(GetAbilityLevel());
	DamageTypes.DarkDamage = Damage.DarkDamage.GetValueAtLevel(GetAbilityLevel());
	
	return DamageTypes;
}

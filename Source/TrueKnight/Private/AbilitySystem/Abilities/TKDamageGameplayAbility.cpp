// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TKDamageGameplayAbility.h"

#include "TKGameplayTags.h"

FDamageTypeByLevel UTKDamageGameplayAbility::GetDamageAtAbilityLevel() const
{
	FDamageTypeByLevel Damage;

	// Map of tags to pointers of FScalableFloat members in FTKDamageType
	TMap<FGameplayTag, float FDamageTypeByLevel::*> DamageMap = {
		{FTKGameplayTags::Get().DamageType_TrueDamage, &FDamageTypeByLevel::TrueDamage},
		{FTKGameplayTags::Get().DamageType_Physical, &FDamageTypeByLevel::PhysicalDamage},
		{FTKGameplayTags::Get().DamageType_Magic, &FDamageTypeByLevel::MagicDamage},
		{FTKGameplayTags::Get().DamageType_Fire, &FDamageTypeByLevel::FireDamage},
		{FTKGameplayTags::Get().DamageType_Cold, &FDamageTypeByLevel::ColdDamage},
		{FTKGameplayTags::Get().DamageType_Lightning, &FDamageTypeByLevel::LightningDamage},
		{FTKGameplayTags::Get().DamageType_Poison, &FDamageTypeByLevel::PoisonDamage},
		{FTKGameplayTags::Get().DamageType_Holy, &FDamageTypeByLevel::HolyDamage},
		{FTKGameplayTags::Get().DamageType_Dark, &FDamageTypeByLevel::DarkDamage},
	};

	// Iterate over the map and populate the damage values
	for (const auto& Elem : DamageMap)
	{
		const FGameplayTag& Tag = Elem.Key;
		float FDamageTypeByLevel::* DamagePtr = Elem.Value;
        
		const FScalableFloat* DamageValue = DamageTypes.Find(Tag);
		if (DamageValue)
		{
			Damage.*DamagePtr = DamageValue->GetValueAtLevel(GetAbilityLevel());
		}
	}
	
	return Damage;
}

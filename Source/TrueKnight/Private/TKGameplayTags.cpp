// Fill out your copyright notice in the Description page of Project Settings.


#include "TKGameplayTags.h"
#include "GameplayTagsManager.h"

FTKGameplayTags FTKGameplayTags::GameplayTags;

void FTKGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FTKGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	// Base Attribute Tags
	AddTag(BaseAttributeTag_Strength, "Attributes.Base.Strength", "Increases physical damage done.");
	AddTag(BaseAttributeTag_Vitality, "Attributes.Base.Vitality", "Increases max health and armor.");
	AddTag(BaseAttributeTag_Intelligence, "Attributes.Base.Intelligence", "Increases elemental damage done.");
	AddTag(BaseAttributeTag_Insight, "Attributes.Base.Insight", "Increases max mana, elemental magic resistance and more.");
	AddTag(BaseAttributeTag_Instinct, "Attributes.Base.Instinct", "Increases chance to critical damage, armor penetration and vulnerability damage.");
	AddTag(BaseAttributeTag_Devotion, "Attributes.Base.Devotion", "Increases holy damage and resistance but reduces dark resistance.");
	AddTag(BaseAttributeTag_Blasphemy, "Attributes.Base.Blasphemy", "Increases dark damage and resistance but reduces holy resistance.");

	// Secondary Attribute Tags
	AddTag(SecondaryAttributeTag_MaxHealth, "Attributes.Secondary.MaxHealth", "Increases the maximum health the player can have.");
	AddTag(SecondaryAttributeTag_MaxMana, "Attributes.Secondary.MaxMana", "Increases the maximum Mana the player can have.");
	AddTag(SecondaryAttributeTag_MaxStamina, "Attributes.Secondary.MaxStamina", "Increases the maximum Stamina the player can have, affected by Vitality or Insight (the highest).");
	
	AddTag(SecondaryAttributeTag_Armor, "Attributes.Secondary.Armor", "Reduces physical damage taken.");
	AddTag(SecondaryAttributeTag_FireResistance, "Attributes.Secondary.FireResistance", "Reduces fire damage taken.");
	AddTag(SecondaryAttributeTag_LightningResistance, "Attributes.Secondary.LightningResistance", "Reduces lightning damage taken.");
	AddTag(SecondaryAttributeTag_ColdResistance, "Attributes.Secondary.ColdResistance", "Reduces cold damage taken.");
	AddTag(SecondaryAttributeTag_HolyResistance, "Attributes.Secondary.HolyResistance", "Reduces holy damage taken.");
	AddTag(SecondaryAttributeTag_DarkResistance, "Attributes.Secondary.DarkResistance", "Reduces dark damage taken.");

	AddTag(SecondaryAttributeTag_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "Amount of health regenerated each second.");
	AddTag(SecondaryAttributeTag_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "Amount of mana regenerated each second.");
	AddTag(SecondaryAttributeTag_StaminaRegeneration, "Attributes.Secondary.StaminaRegeneration", "Amount of stamina regenerated each second.");

	AddTag(SecondaryAttributeTag_PhysicalDamage, "Attributes.Secondary.PhysicalDamage", "Physical damage done before calculations.");
	AddTag(SecondaryAttributeTag_ElementalDamage, "Attributes.Secondary.ElementalDamage", "Elemental damage done before calculations.");
	AddTag(SecondaryAttributeTag_HolyDamage, "Attributes.Secondary.HolyDamage", "Holy damage done before calculations.");
	AddTag(SecondaryAttributeTag_DarkDamage, "Attributes.Secondary.DarkDamage", "Dark damage done before calculations.");

	AddTag(SecondaryAttributeTag_BlockChance, "Attributes.Secondary.BlockChance", "Chance to block an incoming attack.");
	AddTag(SecondaryAttributeTag_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "Percentage of target's armor ignored.");
	AddTag(SecondaryAttributeTag_CriticalChance, "Attributes.Secondary.CriticalChance", "Chance to land a critical hit.");
	AddTag(SecondaryAttributeTag_VulnerabilityDamage, "Attributes.Secondary.VulnerabilityDamage", "Damage multiplier for vulnerable targets.");
	AddTag(SecondaryAttributeTag_CriticalDamage, "Attributes.Secondary.CriticalDamage", "Damage multiplier for critical hits.");

	// Vital Attribute Tags
	AddTag(VitalAttributeTag_Health, "Attributes.Vital.Health", "Amount of damage the player can receive.");
	AddTag(VitalAttributeTag_Mana, "Attributes.Vital.Mana", "Total amount of mana to cast spells.");
	AddTag(VitalAttributeTag_Stamina, "Attributes.Vital.Stamina", "Total amount of stamina to perform actions.");

	// Currency Attribute Tags
	AddTag(CurrencyAttributeTag_Memories, "Attributes.Currency.Memories", "Base currency of the game.");
	AddTag(CurrencyAttributeTag_TimeShards, "Attributes.Currency.TimeShards", "Special currency for unique items, abilities or effects.");
	
}

void FTKGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * TKGameplayTags
 *
 * Singleton containing Native Gameplay Tags
 * With a Singleton you declare a static getter function
 */

struct FTKGameplayTags
{
 
public:
 
    static const FTKGameplayTags& Get() { return GameplayTags; }
    static void InitializeNativeGameplayTags();
	
	/*
	 * Vital Attribute Tags
	 */
	FGameplayTag VitalAttributeTag_Health;
	FGameplayTag VitalAttributeTag_Mana;
	FGameplayTag VitalAttributeTag_Stamina;
	
	/*
	 * Base Attribute Tags
	 */
	FGameplayTag BaseAttributeTag_Strength;
	FGameplayTag BaseAttributeTag_Vitality;
	FGameplayTag BaseAttributeTag_Intelligence;
	FGameplayTag BaseAttributeTag_Insight;
	FGameplayTag BaseAttributeTag_Instinct;
	FGameplayTag BaseAttributeTag_Devotion;
	FGameplayTag BaseAttributeTag_Blasphemy;

	/*
	 * Secondary Attribute Tags
	 */
	FGameplayTag SecondaryAttributeTag_MaxHealth;
	FGameplayTag SecondaryAttributeTag_MaxMana;
	FGameplayTag SecondaryAttributeTag_MaxStamina;
	
    FGameplayTag SecondaryAttributeTag_Armor;
	FGameplayTag SecondaryAttributeTag_FireResistance;
	FGameplayTag SecondaryAttributeTag_LightningResistance;
	FGameplayTag SecondaryAttributeTag_ColdResistance;
	FGameplayTag SecondaryAttributeTag_HolyResistance;
	FGameplayTag SecondaryAttributeTag_DarkResistance;

	FGameplayTag SecondaryAttributeTag_HealthRegeneration;
	FGameplayTag SecondaryAttributeTag_ManaRegeneration;
	FGameplayTag SecondaryAttributeTag_StaminaRegeneration;

	FGameplayTag SecondaryAttributeTag_PhysicalDamage;
	FGameplayTag SecondaryAttributeTag_ElementalDamage;
	FGameplayTag SecondaryAttributeTag_HolyDamage;
	FGameplayTag SecondaryAttributeTag_DarkDamage;

	FGameplayTag SecondaryAttributeTag_BlockChance;
	FGameplayTag SecondaryAttributeTag_ArmorPenetration;
	FGameplayTag SecondaryAttributeTag_CriticalChance;
	FGameplayTag SecondaryAttributeTag_VulnerabilityDamage;
	FGameplayTag SecondaryAttributeTag_CriticalDamage;

	/*
	 * Other Attribute Tags
	 */
	FGameplayTag CurrencyAttributeTag_Memories;
	FGameplayTag CurrencyAttributeTag_TimeShards;

	/*
	 * Message Tags 
	 */
	FGameplayTag MessageTag;
	FGameplayTag MessageTag_HealthMushroom;
	FGameplayTag MessageTag_HealthPotion;
	FGameplayTag MessageTag_ManaPlant;
	FGameplayTag MessageTag_ManaPotion;

	/*
	 * Base tags for attributes
	 */
	FGameplayTag AttributesTag;
	FGameplayTag VitalAttributesTag;
	FGameplayTag BaseAttributesTag;
	FGameplayTag SecondaryAttributesTag;
	FGameplayTag CurrencyTag;
	
protected:

	// Registers all the tags with the GameplayTags Manager
    void AddAllTags(UGameplayTagsManager& Manager);
 
    //Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);
 
private:
 
	static FTKGameplayTags GameplayTags;
};

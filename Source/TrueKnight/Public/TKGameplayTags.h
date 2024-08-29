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
	FGameplayTag SecondaryAttributeTag_MagicResistance;
	FGameplayTag SecondaryAttributeTag_FireResistance;
	FGameplayTag SecondaryAttributeTag_LightningResistance;
	FGameplayTag SecondaryAttributeTag_ColdResistance;
	FGameplayTag SecondaryAttributeTag_PoisonResistance;
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

	/*
	 * Input Tags
	 */
	FGameplayTag InputTag_Primary;
	FGameplayTag InputTag_Secondary;
	FGameplayTag InputTag_Dash;
	FGameplayTag InputTag_Crouch;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Action1;
	FGameplayTag InputTag_Action2;
	FGameplayTag InputTag_Action3;
	FGameplayTag InputTag_Action4;
	FGameplayTag InputTag_Map;
	FGameplayTag InputTag_Menu;
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Down;
	FGameplayTag InputTag_Up;

	/*
	 * Damage Tags
	 */
	
	FGameplayTag DamageType_TrueDamage;
	
	FGameplayTag DamageType_Physical;
	FGameplayTag DamageType_Magic;
	FGameplayTag DamageType_Fire;
	FGameplayTag DamageType_Cold;
	FGameplayTag DamageType_Lightning;
	FGameplayTag DamageType_Poison;
	FGameplayTag DamageType_Holy;
	FGameplayTag DamageType_Dark;
	

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	/*
	 * Effect Tags
	 */

	FGameplayTag EffectTag_HitReact;
	FGameplayTag EffectTag_Death;
	
	/*
	 * Event Tags
	 * These tags are used to trigger something in response to a gameplay event
	 */

	FGameplayTag EventTag_Melee_Basic;
	FGameplayTag EventTag_Spell_Firebolt;
	FGameplayTag EventTag_Wall;
	FGameplayTag EventTag_WallSliding;
	FGameplayTag EventTag_WallHanging;
	FGameplayTag EventTag_LedgeClimb;
	FGameplayTag EventTag_Slide;

	// Ability Tags
	FGameplayTag Abilities_Attack;
	
	// Combat Tags
	FGameplayTag CombatTag_Casting;
	FGameplayTag CombatTag_Attacking;

	/*
	 * Inventory Tags
	 */
	FGameplayTag InventoryTag;
	FGameplayTag InventoryTag_Item;
	FGameplayTag InventoryTag_Key;
	FGameplayTag InventoryTag_Special;
	FGameplayTag InventoryTag_Mark;
	FGameplayTag InventoryTag_Equipment;
	
protected:

	// Registers all the tags with the GameplayTags Manager
    void AddAllTags(UGameplayTagsManager& Manager);
 
    //Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);
 
private:
 
	static FTKGameplayTags GameplayTags;
};

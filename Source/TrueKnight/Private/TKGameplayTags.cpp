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
	// Vital Attribute Tags
	AddTag(VitalAttributeTag_Health, "Attributes.Vital.Health", "Amount of damage the player can receive.");
	AddTag(VitalAttributeTag_Mana, "Attributes.Vital.Mana", "Total amount of mana to cast spells.");
	AddTag(VitalAttributeTag_Stamina, "Attributes.Vital.Stamina", "Total amount of stamina to perform actions.");
	
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
	AddTag(SecondaryAttributeTag_MagicResistance, "Attributes.Secondary.MagicResistance", "Reduces magical damage taken.");
	AddTag(SecondaryAttributeTag_FireResistance, "Attributes.Secondary.FireResistance", "Reduces fire damage taken.");
	AddTag(SecondaryAttributeTag_LightningResistance, "Attributes.Secondary.LightningResistance", "Reduces lightning damage taken.");
	AddTag(SecondaryAttributeTag_ColdResistance, "Attributes.Secondary.ColdResistance", "Reduces cold damage taken.");
	AddTag(SecondaryAttributeTag_PoisonResistance, "Attributes.Secondary.PoisonResistance", "Reduces poison damage taken.");
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

	// Currency Attribute Tags
	AddTag(CurrencyAttributeTag_Memories, "Attributes.Currency.Memories", "Base currency of the game.");
	AddTag(CurrencyAttributeTag_TimeShards, "Attributes.Currency.TimeShards", "Special currency for unique items, abilities or effects.");

	// Message Tags
	AddTag(MessageTag, "Message", "Base tag for the messages");
	AddTag(MessageTag_HealthMushroom, "Message.HealthMushroom", "Send a message to the UI after picking up a Health Mushroom");
	AddTag(MessageTag_HealthPotion, "Message.HealthPotion", "Send a message to the UI after picking up a Health Potion");
	AddTag(MessageTag_ManaPlant, "Message.ManaPlant", "Send a message to the UI after picking up a Mana Plant");
	AddTag(MessageTag_ManaPotion, "Message.ManaPotion", "Send a message to the UI after picking up a Mana Potion");

	// Base tags for attributes
	AddTag(AttributesTag, "Attributes", "");
	AddTag(VitalAttributesTag, "Attributes.Vital", "");
	AddTag(BaseAttributesTag, "Attributes.Base", "");
	AddTag(SecondaryAttributesTag, "Attributes.Secondary", "");
	AddTag(CurrencyTag, "Attributes.Currency", "");

	// Input Tags
	AddTag(InputTag_Primary, "InputTag.Primary", "Input tag associated to the primary attack.");
	AddTag(InputTag_Secondary, "InputTag.Secondary", "Input tag associated to the secondary attack.");
	AddTag(InputTag_Dash, "InputTag.Dash", "Input tag associated to the character's dash.");
	AddTag(InputTag_Crouch, "InputTag.Crouch", "Input tag associated to character's crouching.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Input tag associated to character's jump.");
	AddTag(InputTag_Action1, "InputTag.Action1", "Input tag associated to any action or gameplay ability.");
	AddTag(InputTag_Action2, "InputTag.Action2", "Input tag associated to any action or gameplay ability.");
	AddTag(InputTag_Action3, "InputTag.Action3", "Input tag associated to any action or gameplay ability.");
	AddTag(InputTag_Action4, "InputTag.Action4", "Input tag associated to any action or gameplay ability.");
	AddTag(InputTag_Map, "InputTag.Map", "Input tag associated to opening the Map.");
	AddTag(InputTag_Menu, "InputTag.Menu", "Input tag associated to opening the Pause Menu.");
	AddTag(InputTag_Move, "InputTag.Move", "Input tag associated to moving the character.");
	AddTag(InputTag_Down, "InputTag.Down", "Input tag to drop while hanging off a ledge.");
	AddTag(InputTag_Up, "InputTag.Up", "Input tag to go up from hanging off a ledge.");

	// Damage Tags
	AddTag(DamageType_TrueDamage, "DamageType.TrueDamage", "True Damage.");
	AddTag(DamageType_Physical, "DamageType.Physical", "Physical Damage.");
	AddTag(DamageType_Magic, "DamageType.Magic", "Magic Damage.");
	AddTag(DamageType_Fire, "DamageType.Fire", "Fire Damage.");
	AddTag(DamageType_Cold, "DamageType.Cold", "Cold Damage.");
	AddTag(DamageType_Lightning, "DamageType.Lightning", "Lightning Damage.");
	AddTag(DamageType_Poison, "DamageType.Poison", "Poison Damage.");
	AddTag(DamageType_Holy, "DamageType.Holy", "Holy Damage.");
	AddTag(DamageType_Dark, "DamageType.Dark", "Dark Damage.");

	// Map of DamageTypes to Resistances
	DamageTypesToResistances.Add(DamageType_TrueDamage, FGameplayTag());
	DamageTypesToResistances.Add(DamageType_Physical, SecondaryAttributeTag_Armor);
	DamageTypesToResistances.Add(DamageType_Magic, SecondaryAttributeTag_MagicResistance);
	DamageTypesToResistances.Add(DamageType_Fire, SecondaryAttributeTag_FireResistance);
	DamageTypesToResistances.Add(DamageType_Cold, SecondaryAttributeTag_ColdResistance);
	DamageTypesToResistances.Add(DamageType_Lightning, SecondaryAttributeTag_LightningResistance);
	DamageTypesToResistances.Add(DamageType_Poison, SecondaryAttributeTag_PoisonResistance);
	DamageTypesToResistances.Add(DamageType_Holy, SecondaryAttributeTag_HolyResistance);
	DamageTypesToResistances.Add(DamageType_Dark, SecondaryAttributeTag_DarkResistance);

	// Effect Tags
	AddTag(EffectTag_HitReact, "Effect.HitReact", "HitReact");
	AddTag(EffectTag_Death, "Effect.Death", "Death");

	// Event Tags
	AddTag(EventTag_Melee_Basic, "Event.Melee.Basic", "Event tag to send the basic melee attack event.");
	AddTag(EventTag_Spell_Firebolt, "Event.Spell.Firebolt", "Event tag to send the Firebolt event.");
	AddTag(EventTag_Wall, "Event.Wall", "The character is sliding a wall.");
	AddTag(EventTag_WallSliding, "Event.Wall.Sliding", "The character is sliding a wall.");
	AddTag(EventTag_WallHanging, "Event.Wall.Hanging", "The character is hanging from a wall.");
	AddTag(EventTag_LedgeClimb, "Event.Wall.Climb", "Event trigger to climb a wall.");
	AddTag(EventTag_Slide, "Event.Slide", "Event trigger to slide.");

	// Ability Tags
	AddTag(Abilities_Attack, "Abilities.Attack", "Ability tag to handle attacks.");
	
	// Combat Tags
	AddTag(CombatTag_Attacking, "Combat.Attacking", "Combat tag to melee attacks.");
	AddTag(CombatTag_Casting, "Combat.Casting", "Combat tag to cast spells.");

	// Inventory Tags
	AddTag(InventoryTag, "InventoryTag", "");
	AddTag(InventoryTag_Item, "InventoryTag.Item", "");
	AddTag(InventoryTag_Key, "InventoryTag.Key", "");
	AddTag(InventoryTag_Mark, "InventoryTag.Mark", "");
	AddTag(InventoryTag_Special, "InventoryTag.Special", "");
	AddTag(InventoryTag_Equipment, "InventoryTag.Equipment", "");
}


void FTKGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TagComment));
}

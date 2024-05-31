// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TKAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UTKAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/*************************************
	 ********** Base Attributes **********
	 *************************************/
	// Increases physical melee damage
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Strength);
	// Increases max health and armor
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Vitality);

	// Increases elemental magic damage
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Intelligence);
	// Increases max mana and elemental magic resistance
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Insight;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Insight);
	// Increases chance to critical damage, armor penetration and vulnerability damage
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Instinct;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Instinct);

	// Increases holy damage and resistance
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Devotion;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Devotion);
	// Increases dark damage and resistance
	UPROPERTY(BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Blasphemy;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Blasphemy);

	/**************************************
	 ******** Secondary Attributes ********
	 **************************************/

	// All the secondary attributes will be affected by the equipment

	// The maximum health the player can have, affected by Vitality
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxHealth);
	// The maximum Mana the player can have, affected by Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxMana);
	// The maximum Stamina the player can have, affected by Vitality and Insight (takes the highest)
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxStamina);
	
	// Reduces damage taken from physical damage, affected by Vitality
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Armor);
	// Reduces damage taken by Fire type damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, FireResistance);
	// Reduces damage taken by Thunder type damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, LightningResistance);
	// Reduces damage taken by Cold type damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ColdResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ColdResistance);
	// Reduces the damage taken by Holy type damage, affected by Devotion (+) and Blasphemy (-)
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData HolyResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, HolyResistance);
	// Reduces the damage taken by Dark type damage, affected by Devotion (-) and Blasphemy (+)
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData DarkResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, DarkResistance);

	// Increases the amount of Health regenerated each second
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, HealthRegeneration);
	// Increases the amount of Mana regenerated each second, affected by Intelligence and Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ManaRegeneration);
	// Increases the amount of Stamina regenerated each second, affected by Vitality and Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, StaminaRegeneration);

	// Increases the damage done by physical attacks, affected by Strength
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, PhysicalDamage);
	// Increases the damage done with elemental damage, affected by Intelligence
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ElementalDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ElementalDamage);
	// Increases the damage done by Holy type damage, affected by Devotion
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData HolyDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, HolyDamage);
	// Increases the damage done by Dark type damage, affected by Blasphemy
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData DarkDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, DarkDamage);

	// Increases the chance to block an attack, affected by Instinct
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, BlockChance);
	// Ignores a percentage of the target's armor, affected by Instinct
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ArmorPenetration);
	// Increases the chance to get critical hits, affected by Instinct
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, CriticalChance);
	// Increases the damage done by vulnerability, affected by Insight
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData VulnerabilityDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, VulnerabilityDamage);
	// Increases the damage done by critical hits, affected by Strength
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, CriticalDamage);
	
	
	
	/**************************************
	 ********** Vital Attributes **********
	 **************************************/
	
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Stamina);

	/**************************************
	 ********** Other Attributes **********
	 **************************************/

	UPROPERTY(BlueprintReadOnly, Category = "Other Attributes")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Experience);
	UPROPERTY(BlueprintReadOnly, Category = "Other Attributes")
	FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxExperience);

	// Main Currency
	UPROPERTY(BlueprintReadOnly, Category = "Other Attributes")
	FGameplayAttributeData Memories;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Memories);
	// Special Currency
	UPROPERTY(BlueprintReadOnly, Category = "Other Attributes")
	FGameplayAttributeData TimeShards;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, TimeShards);

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};

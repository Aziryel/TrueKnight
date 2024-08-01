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

// typedef is specific to the FGameplayAttribute Signature, but TStaticFuncPtr is generic to any signature chosen.
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UTKAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	/**************************************
	 ********** Vital Attributes **********
	 **************************************/
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldHMana) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Stamina);
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	
	/*************************************
	 ********** Base Attributes **********
	 *************************************/
	// Increases physical melee damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Base Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	// Increases max health and armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vitality, Category = "Base Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Vitality);
	UFUNCTION()
	void OnRep_Vitality(const FGameplayAttributeData& OldVitality) const;

	// Increases elemental magic damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Base Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	// Increases max mana and elemental magic resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Insight, Category = "Base Attributes")
	FGameplayAttributeData Insight;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Insight);
	UFUNCTION()
	void OnRep_Insight(const FGameplayAttributeData& OldInsight) const;
	// Increases chance to critical damage, armor penetration and vulnerability damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Instinct, Category = "Base Attributes")
	FGameplayAttributeData Instinct;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Instinct);
	UFUNCTION()
	void OnRep_Instinct(const FGameplayAttributeData& OldInstinct) const;

	// Increases holy damage and resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Devotion, Category = "Base Attributes")
	FGameplayAttributeData Devotion;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Devotion);
	UFUNCTION()
	void OnRep_Devotion(const FGameplayAttributeData& OldDevotion) const;
	// Increases dark damage and resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Blasphemy, Category = "Base Attributes")
	FGameplayAttributeData Blasphemy;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Blasphemy);
	UFUNCTION()
	void OnRep_Blasphemy(const FGameplayAttributeData& OldBlasphemy) const;

	/**************************************
	 ******** Secondary Attributes ********
	 **************************************/

	// All the secondary attributes will be affected by the equipment

	// The maximum health the player can have, affected by Vitality
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	// The maximum Mana the player can have, affected by Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	// The maximum Stamina the player can have, affected by Vitality and Insight (takes the highest)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Secondary Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxStamina);
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	
	// Reduces damage taken from physical damage, affected by Vitality
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	// Reduces damage taken from magical damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, Category = "Secondary Attributes")
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MagicResistance);
	UFUNCTION()
	void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;
	// Reduces damage taken by Fire type damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Secondary Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, FireResistance);
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;
	// Reduces damage taken by Thunder type damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Secondary Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, LightningResistance);
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;
	// Reduces damage taken by Cold type damage, affected by Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ColdResistance, Category = "Secondary Attributes")
	FGameplayAttributeData ColdResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ColdResistance);
	UFUNCTION()
	void OnRep_ColdResistance(const FGameplayAttributeData& OldColdResistance) const;
	// Reduces damage taken from poison damage, affected by Vitality
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PoisonResistance, Category = "Secondary Attributes")
	FGameplayAttributeData PoisonResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, PoisonResistance);
	UFUNCTION()
	void OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const;
	// Reduces the damage taken by Holy type damage, affected by Devotion (+) and Blasphemy (-)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HolyResistance, Category = "Secondary Attributes")
	FGameplayAttributeData HolyResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, HolyResistance);
	UFUNCTION()
	void OnRep_HolyResistance(const FGameplayAttributeData& OldHolyResistance) const;
	// Reduces the damage taken by Dark type damage, affected by Devotion (-) and Blasphemy (+)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DarkResistance, Category = "Secondary Attributes")
	FGameplayAttributeData DarkResistance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, DarkResistance);
	UFUNCTION()
	void OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance) const;

	// Increases the amount of Health regenerated each second
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	// Increases the amount of Mana regenerated each second, affected by Intelligence and Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	// Increases the amount of Stamina regenerated each second, affected by Vitality and Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, StaminaRegeneration);
	UFUNCTION()
	void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const;

	// Increases the damage done by physical attacks, affected by Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamage, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, PhysicalDamage);
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const;
	// Increases the damage done with elemental damage, affected by Intelligence
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ElementalDamage, Category = "Secondary Attributes")
	FGameplayAttributeData ElementalDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ElementalDamage);
	UFUNCTION()
	void OnRep_ElementalDamage(const FGameplayAttributeData& OldElementalDamage) const;
	// Increases the damage done by Holy type damage, affected by Devotion
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HolyDamage, Category = "Secondary Attributes")
	FGameplayAttributeData HolyDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, HolyDamage);
	UFUNCTION()
	void OnRep_HolyDamage(const FGameplayAttributeData& OldHolyDamage) const;
	// Increases the damage done by Dark type damage, affected by Blasphemy
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DarkDamage, Category = "Secondary Attributes")
	FGameplayAttributeData DarkDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, DarkDamage);
	UFUNCTION()
	void OnRep_DarkDamage(const FGameplayAttributeData& OldDarkDamage) const;

	// Increases the chance to block an attack, affected by Instinct
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	// Ignores a percentage of the target's armor, affected by Instinct
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	// Increases the chance to get critical hits, affected by Instinct
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, CriticalChance);
	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance) const;
	// Increases the damage done by vulnerability, affected by Insight
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_VulnerabilityDamage, Category = "Secondary Attributes")
	FGameplayAttributeData VulnerabilityDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, VulnerabilityDamage);
	UFUNCTION()
	void OnRep_VulnerabilityDamage(const FGameplayAttributeData& OldVulnerabilityDamage) const;
	// Increases the damage done by critical hits, affected by Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, CriticalDamage);
	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const;

	/**************************************
	 ********** Other Attributes **********
	 **************************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Experience, Category = "Other Attributes")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Experience);
	UFUNCTION()
	void OnRep_Experience(const FGameplayAttributeData& OldExperience) const;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxExperience, Category = "Other Attributes")
	FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, MaxExperience);
	UFUNCTION()
	void OnRep_MaxExperience(const FGameplayAttributeData& OldMaxExperience) const;

	// Main Currency
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Memories, Category = "Other Attributes")
	FGameplayAttributeData Memories;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, Memories);
	UFUNCTION()
	void OnRep_Memories(const FGameplayAttributeData& OldMemories) const;
	// Special Currency
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeShards, Category = "Other Attributes")
	FGameplayAttributeData TimeShards;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, TimeShards);
	UFUNCTION()
	void OnRep_TimeShards(const FGameplayAttributeData& OldTimeShards) const;

	// Attack Related Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ComboCounter, Category = "Attack Attributes")
	FGameplayAttributeData ComboCounter;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, ComboCounter);
	UFUNCTION()
	void OnRep_ComboCounter(const FGameplayAttributeData& OldComboCounter) const;

	/**************************************
	 ********** Meta Attributes **********
	 **************************************/

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UTKAttributeSet, IncomingDamage);

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};


// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "TKGameplayTags.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

UTKAttributeSet::UTKAttributeSet()
{
	const FTKGameplayTags& GameplayTags = FTKGameplayTags::Get();
	
	// Base Attributes
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Vitality, GetVitalityAttribute);
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Insight, GetInsightAttribute);
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Instinct, GetInstinctAttribute);
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Devotion, GetDevotionAttribute);
	TagsToAttributes.Add(GameplayTags.BaseAttributeTag_Blasphemy, GetBlasphemyAttribute);

	// Secondary Attributes
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MaxStamina, GetMaxStaminaAttribute);
	
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_FireResistance, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_LightningResistance, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ColdResistance, GetColdResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_HolyResistance, GetHolyResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_DarkResistance, GetDarkResistanceAttribute);

	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_StaminaRegeneration, GetStaminaRegenerationAttribute);
	
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_PhysicalDamage, GetPhysicalDamageAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ElementalDamage, GetElementalDamageAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_HolyDamage, GetHolyDamageAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_DarkDamage, GetDarkDamageAttribute);

	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_CriticalChance, GetCriticalChanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_VulnerabilityDamage, GetVulnerabilityDamageAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_CriticalDamage, GetCriticalDamageAttribute);
	
}

void UTKAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	/******************************************************************************************************
	 ************** Only use this for clamping the attributes like Stamina, Mana and Stamina **************
	 *********** We have to clamp again in PostGameplayEffectExecute to get the correct clamp *************
	 ******************************************************************************************************/
	
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	if (Attribute == GetComboCounterAttribute())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, FString::Printf(TEXT("Combo: %f"), NewValue));
	}
}

void UTKAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	// Source = causer and Target = target (owner of this attribute set)
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (!Props.SourceController && Props.SourceAvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UTKAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	/*****************************************************************************************************************
	 ******* We clamp setting the attribute so we get the correct value after the gameplay effect is applied *********
	 *****************************************************************************************************************/
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
}


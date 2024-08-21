// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemBlueprintLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/TKPlayerController.h"

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
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_FireResistance, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_LightningResistance, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ColdResistance, GetColdResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_PoisonResistance, GetPoisonResistanceAttribute);
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

void UTKAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Vital Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Stamina, COND_None, REPNOTIFY_Always);

	//Base Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Insight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Instinct, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Devotion, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Blasphemy, COND_None, REPNOTIFY_Always);

	//Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, ColdResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, PoisonResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, HolyResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, DarkResistance, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, StaminaRegeneration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, ElementalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, HolyDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, DarkDamage, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, VulnerabilityDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, CriticalDamage, COND_None, REPNOTIFY_Always);

	//Other Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Experience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, MaxExperience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, Memories, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, TimeShards, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTKAttributeSet, ComboCounter, COND_None, REPNOTIFY_Always);
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
		GEngine->AddOnScreenDebugMessage(10, 2.f, FColor::Magenta, FString::Printf(TEXT("Combo: %f"), NewValue));
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
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);

		if(LocalIncomingDamage > 0 && GetHealth() > 0)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FTKGameplayTags::Get().EffectTag_Death);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FTKGameplayTags::Get().EffectTag_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			
			const bool bBlockedHit = UTKAbilitySystemBlueprintLibrary::IsBlockedHit(Props.EffectContextHandle);
			const bool bCriticalHit = UTKAbilitySystemBlueprintLibrary::IsCriticalHit(Props.EffectContextHandle);
			ShowFloatingText(Props, LocalIncomingDamage, bBlockedHit, bCriticalHit);
		}
	}
}

void UTKAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const 
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (ATKPlayerController* PC = Cast<ATKPlayerController>(Props.SourceCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
		}	
	}
}

void UTKAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Health, OldHealth);
}

void UTKAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Mana, OldMana);
}

void UTKAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Stamina, OldStamina);
}

void UTKAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Strength, OldStrength);
}

void UTKAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Vitality, OldVitality);
}

void UTKAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Intelligence, OldIntelligence);
}

void UTKAttributeSet::OnRep_Insight(const FGameplayAttributeData& OldInsight) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Insight, OldInsight);
}

void UTKAttributeSet::OnRep_Instinct(const FGameplayAttributeData& OldInstinct) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Instinct, OldInstinct);
}

void UTKAttributeSet::OnRep_Devotion(const FGameplayAttributeData& OldDevotion) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Devotion, OldDevotion);
}

void UTKAttributeSet::OnRep_Blasphemy(const FGameplayAttributeData& OldBlasphemy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Blasphemy, OldBlasphemy);
}

void UTKAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, MaxHealth, OldMaxHealth);
}

void UTKAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, MaxMana, OldMaxMana);
}

void UTKAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, MaxStamina, OldMaxStamina);
}

void UTKAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Armor, OldArmor);
}

void UTKAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, MagicResistance, OldMagicResistance);
}

void UTKAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, FireResistance, OldFireResistance);
}

void UTKAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, LightningResistance, OldLightningResistance);
}

void UTKAttributeSet::OnRep_ColdResistance(const FGameplayAttributeData& OldColdResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, ColdResistance, OldColdResistance);
}

void UTKAttributeSet::OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, PoisonResistance, OldPoisonResistance);
}

void UTKAttributeSet::OnRep_HolyResistance(const FGameplayAttributeData& OldHolyResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, HolyResistance, OldHolyResistance);
}

void UTKAttributeSet::OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, DarkResistance, OldDarkResistance);
}

void UTKAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UTKAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UTKAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, StaminaRegeneration, OldStaminaRegeneration);
}

void UTKAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, PhysicalDamage, OldPhysicalDamage);
}

void UTKAttributeSet::OnRep_ElementalDamage(const FGameplayAttributeData& OldElementalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, ElementalDamage, OldElementalDamage);
}

void UTKAttributeSet::OnRep_HolyDamage(const FGameplayAttributeData& OldHolyDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, HolyDamage, OldHolyDamage);
}

void UTKAttributeSet::OnRep_DarkDamage(const FGameplayAttributeData& OldDarkDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, DarkDamage, OldDarkDamage);
}

void UTKAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, BlockChance, OldBlockChance);
}

void UTKAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UTKAttributeSet::OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, CriticalChance, OldCriticalChance);
}

void UTKAttributeSet::OnRep_VulnerabilityDamage(const FGameplayAttributeData& OldVulnerabilityDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, VulnerabilityDamage, OldVulnerabilityDamage);
}

void UTKAttributeSet::OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, CriticalDamage, OldCriticalDamage);
}

void UTKAttributeSet::OnRep_Experience(const FGameplayAttributeData& OldExperience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Experience, OldExperience);
}

void UTKAttributeSet::OnRep_MaxExperience(const FGameplayAttributeData& OldMaxExperience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, MaxExperience, OldMaxExperience);
}

void UTKAttributeSet::OnRep_Memories(const FGameplayAttributeData& OldMemories) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, Memories, OldMemories);
}

void UTKAttributeSet::OnRep_TimeShards(const FGameplayAttributeData& OldTimeShards) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, TimeShards, OldTimeShards);
}

void UTKAttributeSet::OnRep_ComboCounter(const FGameplayAttributeData& OldComboCounter) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTKAttributeSet, ComboCounter, OldComboCounter);
}
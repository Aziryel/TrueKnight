// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "TKAbilityTypes.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Interaction/CombatInterface.h"

// Struct to be used locally only
struct TKDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage);
	
	TKDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, CriticalDamage, Source, false);
	}
};

static const TKDamageStatics& DamageStatics()
{
	static TKDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	// We need to get the EffectContextHandle to set the custom properties in the custom FTKGameplayEffectContext
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	// Gather tags from Source and Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set By Caller magnitude
	float TrueDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_TrueDamage);
	float PhysicalDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Physical);
	float MagicDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Magic);
	float FireDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Fire);
	float ColdDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Cold);
	float LightningDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Lightning);
	float PoisonDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Poison);
	float HolyDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Holy);
	float DarkDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Dark);
	float TotalDamage = 0.f;
	
	if (PhysicalDamage > 0.f)
	{
		// Capture BlockChance on Target and determine if there was a successful block
		// If Block, halve the damage
		float TargetBlockChance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
		TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

		const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
		UTKAbilitySystemBlueprintLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
		
		PhysicalDamage = bBlocked ? PhysicalDamage / 2.f : PhysicalDamage;
		
		// Armor Penetration ignores a percentage of the target armor
		float TargetArmor = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
		TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

		float SourceArmorPenetration = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
		SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

		// We take the armor penetration into consideration to calculate the target's final armor
		const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration) / 100.f;
		PhysicalDamage *= (100 - EffectiveArmor) / 100.f;

		TotalDamage += PhysicalDamage;
	}
	if (MagicDamage > 0.f)
	{
		TotalDamage += MagicDamage;
	}
	if (FireDamage > 0.f)
	{
		TotalDamage += FireDamage;
	}
	if (ColdDamage > 0.f)
	{
		TotalDamage += ColdDamage;
	}
	if (LightningDamage > 0.f)
	{
		TotalDamage += LightningDamage;
	}
	if (PoisonDamage > 0.f)
	{
		TotalDamage += PoisonDamage;
	}
	if (HolyDamage > 0.f)
	{
		TotalDamage += HolyDamage;	
	}
	if (DarkDamage > 0.f)
	{
		TotalDamage += DarkDamage;
	}

	// The critical hit will take into account the complete damage, even elemental and magic damage.
	float SourceCriticalChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalChanceDef, EvaluationParameters, SourceCriticalChance);
	SourceCriticalChance = FMath::Max<float>(SourceCriticalChance, 0.f);

	float SourceCriticalDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalDamageDef, EvaluationParameters, SourceCriticalDamage);
	SourceCriticalDamage = FMath::Max<float>(SourceCriticalDamage, 0.f);

	// We multiply the damage by the critical damage
	const bool bCritical = FMath::RandRange(1, 100) < SourceCriticalChance;
	UTKAbilitySystemBlueprintLibrary::SetIsCriticalHit(EffectContextHandle, bCritical);
	
	TotalDamage = bCritical ? TotalDamage * SourceCriticalDamage : TotalDamage;
	
	// Add the True Damage to the total damage, it doesn't take into consideration resistance nor critical hits.
	TotalDamage += TrueDamage;
	// Add the damage set by caller to the meta-attribute IncomingDamage
	const FGameplayModifierEvaluatedData EvaluatedData(UTKAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, TotalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

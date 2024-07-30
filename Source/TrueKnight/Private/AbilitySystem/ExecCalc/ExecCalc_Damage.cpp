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
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HolyResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DarkResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	TKDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, CriticalDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, MagicResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, ColdResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, PoisonResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, HolyResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, DarkResistance, Target, false);

		const FTKGameplayTags& Tags = FTKGameplayTags::Get();
		Tags.InitializeNativeGameplayTags();
		
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_MagicResistance, MagicResistanceDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_FireResistance, FireResistanceDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_ColdResistance, ColdResistanceDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_LightningResistance, LightningResistanceDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_PoisonResistance, PoisonResistanceDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_HolyResistance, HolyResistanceDef);
		TagsToCaptureDefs.Add(Tags.SecondaryAttributeTag_DarkResistance, DarkResistanceDef);
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

	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ColdResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().HolyResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().DarkResistanceDef);
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

	float TotalDamage = 0.f;
	
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FTKGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		
		if (DamageTypeTag != FTKGameplayTags::Get().DamageType_TrueDamage)
		{
			checkf(DamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag [%s] in ExecCalc_Damage."), *ResistanceTag.ToString());
			const FGameplayEffectAttributeCaptureDefinition CaptureDef = DamageStatics().TagsToCaptureDefs[ResistanceTag];
			
			float Resistance = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().TagsToCaptureDefs[ResistanceTag], EvaluationParameters, Resistance);
			Resistance = FMath::Clamp(Resistance, 0.f, 100.f);
			
			if (DamageTypeTag == FTKGameplayTags::Get().DamageType_Physical && DamageTypeValue > 0.f)
			{
				// Capture BlockChance on Target and determine if there was a successful block
				// If Block, halve the damage
				float TargetBlockChance = 0.f;
				ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
				TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

				const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
				UTKAbilitySystemBlueprintLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
			
				DamageTypeValue = bBlocked ? DamageTypeValue / 2.f : DamageTypeValue;

				float SourceArmorPenetration = 0.f;
				ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
				SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

				// We take the armor penetration into consideration to calculate the target's final armor
				const float EffectiveArmor = Resistance *= (100 - SourceArmorPenetration) / 100.f;
				DamageTypeValue *= (100 - EffectiveArmor) / 100.f;
			}
			else
			{
				DamageTypeValue *=  (100.f - Resistance) / 100.f;
			}
			
		}

		TotalDamage += DamageTypeValue;
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
	
	/*// Add the True Damage to the total damage, it doesn't take into consideration resistance nor critical hits.
	TotalDamage += TrueDamage;*/
	
	// Add the damage set by caller to the meta-attribute IncomingDamage
	const FGameplayModifierEvaluatedData EvaluatedData(UTKAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, TotalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

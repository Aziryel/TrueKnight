// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_StaminaRegen.h"

#include "AbilitySystem/TKAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_StaminaRegen::UMMC_StaminaRegen()
{
	VitalityDef.AttributeToCapture = UTKAttributeSet::GetVitalityAttribute();
	VitalityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VitalityDef.bSnapshot = false;
	
	InsightDef.AttributeToCapture = UTKAttributeSet::GetInsightAttribute();
	InsightDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	InsightDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VitalityDef);
	RelevantAttributesToCapture.Add(InsightDef);
}

float UMMC_StaminaRegen::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from Source and Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Vitality = 0.f;
	GetCapturedAttributeMagnitude(VitalityDef, Spec, EvaluationParameters, Vitality);
	Vitality = FMath::Max<float>(Vitality, 0.f);

	float Insight = 0.f;
	GetCapturedAttributeMagnitude(InsightDef, Spec, EvaluationParameters, Insight);
	Insight = FMath::Max<float>(Insight, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	return 0.5f + (Vitality + Insight) * 0.08 + PlayerLevel * 0.06; 
}

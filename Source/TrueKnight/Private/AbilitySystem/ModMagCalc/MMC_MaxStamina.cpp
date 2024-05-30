// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxStamina.h"

#include "AbilitySystem/TKAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxStamina::UMMC_MaxStamina()
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

float UMMC_MaxStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	if (Vitality > Insight)
	{
		return 18.f + 14.f * Vitality + PlayerLevel * 3.f;
	}
	else
	{
		return 18.f + 14.f * Insight + PlayerLevel * 3.f;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/TKAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	InsightDef.AttributeToCapture = UTKAttributeSet::GetInsightAttribute();
	InsightDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	InsightDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(InsightDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from Source and Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Insight = 0.f;
	GetCapturedAttributeMagnitude(InsightDef, Spec, EvaluationParameters, Insight);
	Insight = FMath::Max<float>(Insight, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	return 20.f + 18.f * Insight + PlayerLevel * 4.f;
}

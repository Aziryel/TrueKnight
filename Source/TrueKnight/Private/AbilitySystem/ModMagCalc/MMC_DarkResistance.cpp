// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_DarkResistance.h"

#include "AbilitySystem/TKAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_DarkResistance::UMMC_DarkResistance()
{
	DevotionDef.AttributeToCapture = UTKAttributeSet::GetDevotionAttribute();
	DevotionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DevotionDef.bSnapshot = false;
	
	BlasphemyDef.AttributeToCapture = UTKAttributeSet::GetBlasphemyAttribute();
	BlasphemyDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	BlasphemyDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(DevotionDef);
	RelevantAttributesToCapture.Add(BlasphemyDef);
}

float UMMC_DarkResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from Source and Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Devotion = 0.f;
	GetCapturedAttributeMagnitude(DevotionDef, Spec, EvaluationParameters, Devotion);
	Devotion = FMath::Max<float>(Devotion, 0.f);

	float Blasphemy = 0.f;
	GetCapturedAttributeMagnitude(BlasphemyDef, Spec, EvaluationParameters, Blasphemy);
	Blasphemy = FMath::Max<float>(Blasphemy, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	//TODO: Give player a tag to calculate both attributes as positive, possibly with a hidden passive skill
	return 5.f + (Blasphemy * 0.5f) - (Devotion * 0.5f) + PlayerLevel * 0.1;
}

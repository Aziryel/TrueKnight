// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_StaminaRegen.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UMMC_StaminaRegen : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_StaminaRegen();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition VitalityDef;
	FGameplayEffectAttributeCaptureDefinition InsightDef;
};

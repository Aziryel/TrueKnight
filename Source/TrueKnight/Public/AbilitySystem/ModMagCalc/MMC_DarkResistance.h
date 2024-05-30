// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_DarkResistance.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UMMC_DarkResistance : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_DarkResistance();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition DevotionDef;
	FGameplayEffectAttributeCaptureDefinition BlasphemyDef;
};

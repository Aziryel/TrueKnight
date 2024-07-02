// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TKGameplayAbility.generated.h"

USTRUCT(BlueprintType)
struct FTKDamageType
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat TrueDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat PhysicalDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat MagicDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat FireDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat ColdDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat LightningDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat PoisonDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat HolyDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat DarkDamage;
};

USTRUCT(BlueprintType)
struct FDamageTypeByLevel
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float TrueDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float PhysicalDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float MagicDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float FireDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float ColdDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float LightningDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float PoisonDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float HolyDamage = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	float DarkDamage = 0.f;
};

class UTimelineComponent;
/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FTKDamageType Damage;

	UPROPERTY(EditDefaultsOnly)
	bool bActivateOnGiven = false;

	UFUNCTION(BlueprintPure, Category = "Damage")
	FDamageTypeByLevel GetDamageAtAbilityLevel() const;
	
};

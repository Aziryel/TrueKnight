// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TKGameplayAbility.h"
#include "TKDamageGameplayAbility.generated.h"

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

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKDamageGameplayAbility : public UTKGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure, Category = "Damage")
	FDamageTypeByLevel GetDamageAtAbilityLevel() const;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
};

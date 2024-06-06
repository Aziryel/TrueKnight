// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TKGameplayAbility.h"
#include "TKProjectileAbility.generated.h"

class ATKProjectile;
/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKProjectileAbility : public UTKGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATKProjectile> ProjectileClass;
};

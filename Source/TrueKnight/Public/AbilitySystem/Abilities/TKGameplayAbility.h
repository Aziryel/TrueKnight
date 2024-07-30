// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TKGameplayAbility.generated.h"

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
	
	UPROPERTY(EditDefaultsOnly)
	bool bActivateOnGiven = false;
};

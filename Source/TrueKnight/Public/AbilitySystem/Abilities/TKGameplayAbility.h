// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TrueKnight/TrueKnight.h"
#include "TKGameplayAbility.generated.h"

class UPaperZDAnimSequence;
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

protected:
	
	// Function to play an animation override using the TKCharacterBase along with the TKGameplayAbility.
	// Implementing multiplayer functionality.
	UFUNCTION(BlueprintCallable, Category = "TKAbility")
	void PlayTKAnimationOverride(const UPaperZDAnimSequence* AnimSequence, FName SlotName = FName("DefaultSlot"), float PlayRate = 1.0f, float StartingPosition = 0.0f, const bool bEndAbilityOnCompleted = true);

private:

	UFUNCTION()
	void EndAbilityAfterOnAnimationCompleted();

};

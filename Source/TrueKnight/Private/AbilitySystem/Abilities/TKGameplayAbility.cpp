// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TKGameplayAbility.h"

#include "Character/TKCharacterBase.h"

void UTKGameplayAbility::PlayTKAnimationOverride(const UPaperZDAnimSequence* AnimSequence, FName SlotName, float PlayRate, float StartingPosition, const bool bEndAbilityOnCompleted)
{
	ATKCharacterBase* OwnerCharacter = Cast<ATKCharacterBase>(GetAvatarActorFromActorInfo());
	if (OwnerCharacter && AnimSequence)
	{
		if (bEndAbilityOnCompleted)
		{
			OwnerCharacter->OnAnimationCompleted.AddUniqueDynamic(this, &UTKGameplayAbility::EndAbilityAfterOnAnimationCompleted);
		}
		OwnerCharacter->Play2DMultiAnimation(AnimSequence, SlotName, PlayRate, StartingPosition);
	}
}

void UTKGameplayAbility::EndAbilityAfterOnAnimationCompleted()
{
	K2_EndAbility();
}

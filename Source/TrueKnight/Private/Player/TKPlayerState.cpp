// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TKPlayerState.h"

#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"

ATKPlayerState::ATKPlayerState()
{
	//Create the TKASC for the player character.
	AbilitySystemComponent = CreateDefaultSubobject<UTKAbilitySystemComponent>("AbilitySystemComponent");

	//Create the TKAttributeSet for the player character.
	AttributeSet = CreateDefaultSubobject<UTKAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ATKPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

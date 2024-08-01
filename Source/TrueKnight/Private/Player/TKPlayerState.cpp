// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TKPlayerState.h"

#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Net/UnrealNetwork.h"

ATKPlayerState::ATKPlayerState()
{
	//Create the TKASC for the player character.
	AbilitySystemComponent = CreateDefaultSubobject<UTKAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//Create the TKAttributeSet for the player character.
	AttributeSet = CreateDefaultSubobject<UTKAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void ATKPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATKPlayerState, Level);
}

UAbilitySystemComponent* ATKPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATKPlayerState::OnRep_Level(int32 OldLevel)
{
	
}

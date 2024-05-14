// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKEnemyCharacter.h"

#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"

ATKEnemyCharacter::ATKEnemyCharacter()
{
	//Create the TKASC for the enemy character.
	AbilitySystemComponent = CreateDefaultSubobject<UTKAbilitySystemComponent>("AbilitySystemComponent");

	//Create the TKAttributeSet for the enemy character.
	AttributeSet = CreateDefaultSubobject<UTKAttributeSet>("AttributeSet");
}

void ATKEnemyCharacter::HighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Highligh Actor: %s"), *GetNameSafe(this)));
}

void ATKEnemyCharacter::UnhighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("Unhighligh Actor: %s"), *GetNameSafe(this)));
}

void ATKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

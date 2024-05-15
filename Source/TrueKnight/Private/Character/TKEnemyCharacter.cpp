// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKEnemyCharacter.h"

#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Components/CapsuleComponent.h"

ATKEnemyCharacter::ATKEnemyCharacter()
{
	//Create the TKASC for the enemy character.
	AbilitySystemComponent = CreateDefaultSubobject<UTKAbilitySystemComponent>("AbilitySystemComponent");

	//Create the TKAttributeSet for the enemy character.
	AttributeSet = CreateDefaultSubobject<UTKAttributeSet>("AttributeSet");

	//TODO Make a custom Collision Channel to find abilities overlaps
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetSprite()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetSprite()->SetGenerateOverlapEvents(true);
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

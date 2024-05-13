// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKEnemyCharacter.h"

ATKEnemyCharacter::ATKEnemyCharacter()
{
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
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKCharacterBase.h"

ATKCharacterBase::ATKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ATKCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

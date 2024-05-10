// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKCharacterBase.h"

ATKCharacterBase::ATKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

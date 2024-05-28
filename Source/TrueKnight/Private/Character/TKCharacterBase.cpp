// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKCharacterBase.h"

#include "AbilitySystemComponent.h"

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

void ATKCharacterBase::InitAbilityActorInfo()
{
}

void ATKCharacterBase::InitializeBaseAttributes() const
{
	check(GetAbilitySystemComponent());
	check(DefaultBaseAttributes);
	
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle& EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultBaseAttributes, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), GetAbilitySystemComponent());
}

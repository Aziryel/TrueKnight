// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"

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

FVector ATKCharacterBase::GetCombatSocketLocation()
{
	return GetSprite()->GetSocketLocation(ProjectileSocketName);
}

void ATKCharacterBase::InitAbilityActorInfo()
{
}

void ATKCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(GetAbilitySystemComponent());
	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	// We have to use "this" as the source object because  we are going to use the CombatInterface
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle& EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}

void ATKCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultBaseAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ATKCharacterBase::AddCharacterAbilities()
{
	UTKAbilitySystemComponent* TKASC = CastChecked<UTKAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	TKASC->AddCharacterAbilities(StartupAbilities);
}

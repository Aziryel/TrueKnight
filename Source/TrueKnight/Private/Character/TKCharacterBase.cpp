// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TrueKnight/TrueKnight.h"

ATKCharacterBase::ATKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);

	ProjectileSocketName = "ProjectilePos";
	MeleeSocketName = "HitPos";
}

UAbilitySystemComponent* ATKCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UPaperZDAnimInstance* ATKCharacterBase::GetPaperAnimInstance_Implementation()
{
	return GetAnimInstance();
}

UPaperZDAnimSequence* ATKCharacterBase::GetHitReactAnimSequence_Implementation()
{
	return HitReactSequence;
}

UPaperZDAnimSequence* ATKCharacterBase::GetDeathAnimSequence_Implementation()
{
	return DeathSequence;
}

UPaperZDAnimSequence* ATKCharacterBase::GetProjectileAnimSequence_Implementation()
{
	return ProjectileSequence;
}

UPaperZDAnimSequence* ATKCharacterBase::GetMeleeAnimSequence_Implementation()
{
	return MeleeSequence;
}

EMovementMode ATKCharacterBase::GetMovementMode_Implementation()
{
	return GetCharacterMovement()->MovementMode;
}

FCharacterDataResult ATKCharacterBase::GetCharacterCombatData_Implementation()
{
	FCharacterDataResult Result;

	Result.AnimInstance = GetAnimInstance();
	Result.HitReactAnimSequence = HitReactSequence;
	Result.DeathAnimSequence = DeathSequence;
	Result.ProjectileAnimSequence = ProjectileSequence;
	Result.MeleeAnimSequence = MeleeSequence;
	Result.MovementMode = GetCharacterMovement()->MovementMode;
	
	return Result;
}

void ATKCharacterBase::MulticastHandleDeath_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Die CharacterBase")));
}

void ATKCharacterBase::Die_Implementation(const float DyingLifeSpan)
{
	MulticastHandleDeath();
}

void ATKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector ATKCharacterBase::GetProjectileSocketLocation_Implementation()
{
	return GetSprite()->GetSocketLocation(ProjectileSocketName);
}

FVector ATKCharacterBase::GetMeleeSocketLocation_Implementation()
{
	return GetSprite()->GetSocketLocation(MeleeSocketName);
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
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), GetAbilitySystemComponent());
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

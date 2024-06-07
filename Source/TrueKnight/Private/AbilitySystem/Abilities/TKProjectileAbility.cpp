// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TKProjectileAbility.h"

#include "Actor/TKProjectile.h"
#include "Interaction/CombatInterface.h"

void UTKProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UTKProjectileAbility::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	// We cast to the Combat Interface, so we don't depend on the character base class for anything
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorForwardVector().ToOrientationQuat());
		
		ATKProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATKProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile a gameplay effect spec for causing damage.

		Projectile->FinishSpawning(SpawnTransform);
	}
}

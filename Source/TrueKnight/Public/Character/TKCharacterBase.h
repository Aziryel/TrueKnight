// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"
#include "Interaction/CombatInterface.h"
#include "TKCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

//Dynamic delegate if you want to handle completion logic
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationCompleted);

/**
 * 
 */

//Being abstract means this class will not be loaded into the level
UCLASS(Abstract)
class TRUEKNIGHT_API ATKCharacterBase : public APaperZDCharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	ATKCharacterBase();

	/* Ability System Interface */
	UFUNCTION(BlueprintPure, Category = "TKAbilitySystem")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/* End Ability System Interface */
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UPaperZDAnimInstance* GetPaperAnimInstance_Implementation() override;
	virtual UPaperZDAnimSequence* GetHitReactAnimSequence_Implementation() override;
	virtual UPaperZDAnimSequence* GetDeathAnimSequence_Implementation() override;
	virtual UPaperZDAnimSequence* GetProjectileAnimSequence_Implementation() override;
	virtual UPaperZDAnimSequence* GetMeleeAnimSequence_Implementation() override;
	virtual EMovementMode GetMovementMode_Implementation() override;
	virtual FCharacterDataResult GetCharacterCombatData_Implementation() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	virtual void Die_Implementation(const float DyingLifeSpan) override;
	
	UFUNCTION(Server, Reliable)
	virtual void ServerPlayAnimation(const UPaperZDAnimSequence* AnimSequence, FName SlotName, float PlayRate, float StartingPosition);
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastPlayAnimation(const UPaperZDAnimSequence* AnimSequence, FName SlotName, float PlayRate, float StartingPosition);

	UFUNCTION(BlueprintCallable, Category = "TKAbilities")
	void Play2DMultiAnimation(const UPaperZDAnimSequence* AnimSequence, FName SlotName = FName("DefaultSlot"), float PlayRate = 1.0f, float StartingPosition = 0.0f);

	// Function to simulate the end of the animation
	UFUNCTION(BlueprintCallable, Category = "TKAbilities")
	void OnAnimationEnd();
	
	UPROPERTY(BlueprintAssignable)
	FOnAnimationCompleted OnAnimationCompleted;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName ProjectileSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName MeleeSocketName;
	
	virtual FVector GetProjectileSocketLocation_Implementation() override;
	virtual FVector GetMeleeSocketLocation_Implementation() override;


	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultBaseAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();
	
private:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UPaperZDAnimSequence> ProjectileSequence;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UPaperZDAnimSequence> MeleeSequence;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UPaperZDAnimSequence> HitReactSequence;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UPaperZDAnimSequence> DeathSequence;

};

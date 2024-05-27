// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperZDCharacter.h"
#include "TKCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */

//Being abstract means this class will not be loaded into the level
UCLASS(Abstract)
class TRUEKNIGHT_API ATKCharacterBase : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATKCharacterBase();

	/* Ability System Interface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/* End Ability System Interface */
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();
};

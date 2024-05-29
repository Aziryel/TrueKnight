// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TKCharacterBase.h"
#include "Interaction/TKTargetInterface.h"
#include "TKEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API ATKEnemyCharacter : public ATKCharacterBase, public ITKTargetInterface
{
	GENERATED_BODY()

public:
	ATKEnemyCharacter();

	/* Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	/* End Enemy Interface */

	/* Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/* End Combat Interface */

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TKCharacterBase.h"
#include "TKEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API ATKEnemyCharacter : public ATKCharacterBase
{
	GENERATED_BODY()

public:
	ATKEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	
};

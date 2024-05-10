// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "TKCharacterBase.generated.h"

/**
 * 
 */
//Being abstract means this class will not be loaded into the level

UCLASS(Abstract)
class TRUEKNIGHT_API ATKCharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	ATKCharacterBase();

protected:
	virtual void BeginPlay() override;
};

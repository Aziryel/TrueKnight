// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TKPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API ATKPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATKPlayerController();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> TKContext;
};

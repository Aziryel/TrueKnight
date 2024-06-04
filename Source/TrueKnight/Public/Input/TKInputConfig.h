// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TKInputConfig.generated.h"


USTRUCT(BlueprintType)
struct FTKInputAction
{
	GENERATED_BODY()

	/* Input Action to be linked to a specific tag */
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	/* Gameplay Tag to link the input action to the functionality */
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	/* An Array to include as many Input Actions linked to Gameplay Tags as we want */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTKInputAction> AbilityInputActions;
};

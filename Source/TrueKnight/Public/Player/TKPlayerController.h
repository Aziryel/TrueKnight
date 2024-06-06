// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "TKPlayerController.generated.h"

class UTKAbilitySystemComponent;
class UTKInputConfig;
struct FInputActionValue;
class UInputAction;
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
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> TKContext;

	/* Handles Moving */
	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UTKInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UTKAbilitySystemComponent> TKAbilitySystemComponent;

	UPROPERTY()
	FGameplayTagContainer TagsToIgnore;

	UTKAbilitySystemComponent* GetASC();
};

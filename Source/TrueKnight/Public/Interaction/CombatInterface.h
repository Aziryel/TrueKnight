// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UPaperZDAnimSequence;
class UPaperZDAnimInstance;

// Struct to store different types of data
USTRUCT(BlueprintType)
struct FCharacterDataResult
{
	GENERATED_BODY()

	// For storing the AnimInstance
	UPROPERTY(BlueprintReadOnly, Category="Character Data")
	UPaperZDAnimInstance* AnimInstance;

	// For storing an AnimSequence
	UPROPERTY(BlueprintReadOnly, Category="Character Data")
	UPaperZDAnimSequence* HitReactAnimSequence;

	UPROPERTY(BlueprintReadOnly, Category="Character Data")
	UPaperZDAnimSequence* DeathAnimSequence;

	UPROPERTY(BlueprintReadOnly, Category="Character Data")
	UPaperZDAnimSequence* ProjectileAnimSequence;

	UPROPERTY(BlueprintReadOnly, Category="Character Data")
	UPaperZDAnimSequence* MeleeAnimSequence;

	// For storing the MovementMode
	UPROPERTY(BlueprintReadOnly, Category="Character Data")
	TEnumAsByte<EMovementMode> MovementMode;

	// Default constructor
	FCharacterDataResult()
		: AnimInstance(nullptr), HitReactAnimSequence(nullptr), DeathAnimSequence(nullptr),
		ProjectileAnimSequence(nullptr), MeleeAnimSequence(nullptr), MovementMode(EMovementMode::MOVE_None)
	{
	}
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRUEKNIGHT_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int32 GetPlayerLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	FCharacterDataResult GetCharacterCombatData();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	FVector GetProjectileSocketLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	FVector GetMeleeSocketLocation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UPaperZDAnimInstance* GetPaperAnimInstance();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UPaperZDAnimSequence* GetHitReactAnimSequence();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UPaperZDAnimSequence* GetDeathAnimSequence();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UPaperZDAnimSequence* GetProjectileAnimSequence();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UPaperZDAnimSequence* GetMeleeAnimSequence();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void Die(const float DyingLifeSpan);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	EMovementMode GetMovementMode();
};

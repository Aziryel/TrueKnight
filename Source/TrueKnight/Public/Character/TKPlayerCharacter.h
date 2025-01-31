// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TKCharacterBase.h"
#include "TKPlayerCharacter.generated.h"

class ITKTargetInterface;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API ATKPlayerCharacter : public ATKCharacterBase
{
	GENERATED_BODY()

public:
	ATKPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	/* End Combat Interface */

	// Animation Variables
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	bool bIsClimbing;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	bool bIsGrabbingLedge;
	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	AActor* OverlappingRestrictor;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	//Used to access the Target Interface without using a cast
	TScriptInterface<ITKTargetInterface> ThisActor;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	virtual void InitAbilityActorInfo() override;
	
};

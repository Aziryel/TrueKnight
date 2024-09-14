// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotifyState.h"
#include "MoveCharacterAnimNotifyState.generated.h"

class APaperCharacter;
/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UMoveCharacterAnimNotifyState : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const override;

protected:

	// Curve for controlling X-axis movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UCurveFloat* XMovementCurve;

	// Curve for controlling Z-axis movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UCurveFloat* ZMovementCurve;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Final Location")
	FVector FinalLocation;*/

	void AdjustMovementOnCollision(APaperCharacter* OwningCharacter, const FHitResult& HitResult, float TimeFraction) const;
	
private:

	mutable FVector ForwardVector;
	mutable FVector InitialLocation;
	mutable FVector TargetLocation;
	mutable float ElapsedTime;
	mutable float TotalDuration;
};

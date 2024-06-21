// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotifyState.h"
#include "MoveCharacterAnimNotifyState.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Final Location")
	FVector FinalLocation;
	
private:
	
	mutable FVector InitialLocation;
	mutable FVector TargetLocation;
	mutable float ElapsedTime;
	mutable float TotalDuration;
};

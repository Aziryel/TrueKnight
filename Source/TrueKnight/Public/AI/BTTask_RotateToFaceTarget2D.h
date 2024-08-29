// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_RotateToFaceTarget2D.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UBTTask_RotateToFaceTarget2D : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTTask_RotateToFaceTarget2D();

	// Expose the Actor key to the Behavior Tree editor
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ActorToRotateKey;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	void RotateToFaceTarget(AActor* Enemy, AActor* Target);
	
};

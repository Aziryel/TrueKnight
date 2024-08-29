// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RotateToFaceTarget2D.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RotateToFaceTarget2D::UBTTask_RotateToFaceTarget2D()
{
	NodeName = "Rotate To Face Target 2D";
	ActorToRotateKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RotateToFaceTarget2D, ActorToRotateKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget2D::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AActor* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	// Get the target actor from the blackboard
	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(ActorToRotateKey.SelectedKeyName));
	if (!Target)
	{
		return EBTNodeResult::Failed;
	}

	// Rotate the enemy to face the target
	RotateToFaceTarget(ControlledPawn, Target);

	return EBTNodeResult::Succeeded;
}

void UBTTask_RotateToFaceTarget2D::RotateToFaceTarget(AActor* Enemy, AActor* Target)
{
	FVector EnemyLocation = Enemy->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	// Ignore the Y difference to keep rotation only on the XZ plane
	TargetLocation.Y = EnemyLocation.Y;

	// Calculate the direction to the target
	FVector DirectionToTarget = (TargetLocation - EnemyLocation).GetSafeNormal();

	// Calculate the rotation that faces the target on the XZ plane
	FRotator TargetRotation = DirectionToTarget.Rotation();

	// Apply only the Yaw rotation (around the Y-axis), ignore Roll and Pitch
	FRotator NewRotation = FRotator(0.f, TargetRotation.Yaw, 0.f);

	// Rotate the enemy to face the player
	Enemy->SetActorRotation(NewRotation);
}

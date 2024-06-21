// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/MoveCharacterAnimNotifyState.h"

#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"

void UMoveCharacterAnimNotifyState::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyBegin_Implementation(OwningInstance);
	if (OwningInstance->GetPaperCharacter())
	{
		InitialLocation = OwningInstance->GetPaperCharacter()->GetActorLocation();
		FVector ForwardVector = OwningInstance->GetPaperCharacter()->GetActorForwardVector();
		
		TargetLocation = InitialLocation + FVector(0.f, FinalLocation.Y, FinalLocation.Z) + (ForwardVector * FinalLocation.X);

		ElapsedTime = 0.f;
		TotalDuration = Duration;
	}
}

void UMoveCharacterAnimNotifyState::OnNotifyTick_Implementation(float DeltaTime,
	UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyTick_Implementation(DeltaTime, OwningInstance);

	if (APaperCharacter* OwningCharacter = OwningInstance->GetPaperCharacter())
	{
		ElapsedTime += DeltaTime;
		const float LerpAlpha = FMath::Clamp(ElapsedTime / TotalDuration, 0.f, 0.f);

		const FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, LerpAlpha);

		OwningCharacter->SetActorLocation(NewLocation);
	}
}

void UMoveCharacterAnimNotifyState::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);

	if (APaperCharacter* OwningCharacter = OwningInstance->GetPaperCharacter())
	{
		OwningCharacter->SetActorLocation(TargetLocation);
	}
}

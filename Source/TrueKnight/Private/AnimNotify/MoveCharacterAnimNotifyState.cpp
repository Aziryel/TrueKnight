// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/MoveCharacterAnimNotifyState.h"

#include "PaperZDAnimInstance.h"
#include "PaperZDCharacter.h"

void UMoveCharacterAnimNotifyState::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyBegin_Implementation(OwningInstance);
	
	if (!OwningInstance) return;
	
	if (OwningInstance->GetPaperCharacter())
	{
		// Get the initial location of the character at the start of the animation
		InitialLocation = OwningInstance->GetPaperCharacter()->GetActorLocation();

		// Get the character's forward vector at the start (only calculated once)
		ForwardVector = OwningInstance->GetPaperCharacter()->GetActorForwardVector(); // Store this for later use

		// Initialize timing variables for the animation
		ElapsedTime = 0.f;
		TotalDuration = Duration;
	}
}

void UMoveCharacterAnimNotifyState::OnNotifyTick_Implementation(float DeltaTime,
	UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyTick_Implementation(DeltaTime, OwningInstance);

	if (!OwningInstance) return;

	if (APaperCharacter* OwningCharacter = OwningInstance->GetPaperCharacter())
	{
		// Update elapsed time to control animation progress
		ElapsedTime += DeltaTime;

		// Calculate the lerp alpha based on elapsed time, clamped between 0 and 1
		const float LerpAlpha = FMath::Clamp(ElapsedTime / TotalDuration, 0.f, 1.f);

		// Get the curve values for X and Z movement at the current time in the animation
		float XCurveValue = 0.f;
		float ZCurveValue = 0.f;

		if (XMovementCurve)
		{
			XCurveValue = XMovementCurve->GetFloatValue(LerpAlpha);  // X movement based on curve
		}

		if (ZMovementCurve)
		{
			ZCurveValue = ZMovementCurve->GetFloatValue(LerpAlpha);  // Z movement based on curve
		}

		// Calculate the new location based on the initial location, curve values, and forward vector
		FVector NewLocation = InitialLocation;

		// Use the forward vector to determine movement along the X-axis (left or right)
		NewLocation.X += ForwardVector.X * XCurveValue;

		// Apply the Z movement from the curve
		NewLocation.Z += ZCurveValue;

		// Keep the Y-axis constant for 2D movement
		NewLocation.Y = InitialLocation.Y;  

		// Move the character using SetActorLocation with sweeping to handle collisions
		FHitResult HitResult;
		OwningCharacter->SetActorLocation(NewLocation, true, &HitResult);

		// Handle collision if there is a blocking hit
		if (HitResult.bBlockingHit)
		{
			AdjustMovementOnCollision(OwningCharacter, HitResult, LerpAlpha);
		}
	}
}

void UMoveCharacterAnimNotifyState::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnNotifyEnd_Implementation(OwningInstance);

	if (!OwningInstance) return;

	if (APaperCharacter* OwningCharacter = OwningInstance->GetPaperCharacter())
	{
		// Ensure the character reaches the final location at the end of the animation
		if (XMovementCurve && ZMovementCurve)
		{
			// Get the final X and Z values from the curves at time 1.0 (the end of the animation)
			const float FinalX = XMovementCurve->GetFloatValue(1.0f);
			const float FinalZ = ZMovementCurve->GetFloatValue(1.0f);

			// Calculate the final location using the forward vector (determined at the start of the animation)
			FVector FinalLocation = InitialLocation;
			FinalLocation.X += ForwardVector.X * FinalX;  // Apply the final X offset
			FinalLocation.Z += FinalZ;  // Apply the final Z offset
			FinalLocation.Y = InitialLocation.Y;  // Keep Y constant for 2D movement

			// Set the character's final location, ensuring sweeping to handle any collisions
			OwningCharacter->SetActorLocation(FinalLocation, true);
		}
	}
}

void UMoveCharacterAnimNotifyState::AdjustMovementOnCollision(APaperCharacter* OwningCharacter,
	const FHitResult& HitResult, float TimeFraction) const
{
	// Adjust the character's position based on the hit result, keeping Y unchanged (2D movement)
	FVector AdjustedLocation = HitResult.Location;
	AdjustedLocation.Y = OwningCharacter->GetActorLocation().Y;  // Keep Y constant for 2D movement

	// Offset the character slightly along the hit normal to prevent clipping into the obstacle
	FVector NormalOffset = HitResult.Normal * 5.0f;
	AdjustedLocation += NormalOffset;
	AdjustedLocation.Y = OwningCharacter->GetActorLocation().Y;  // Ensure Y position stays the same

	// Set the new adjusted location after the collision
	OwningCharacter->SetActorLocation(AdjustedLocation);

	// If we hit a surface that's climbable (e.g., mostly vertical)
	if (HitResult.Normal.Z > 0.0f)
	{
		// Calculate a sliding direction along the surface, keeping Y unchanged
		FVector SlideDirection = FVector::CrossProduct(HitResult.Normal, FVector::UpVector).GetSafeNormal();
		SlideDirection.Y = 0;  // Prevent Y movement in 2D

		// Adjust the character's position to slide along the surface while keeping Y constant
		FVector SlideOffset = SlideDirection * 10.0f;
		AdjustedLocation += SlideOffset;
		AdjustedLocation.Y = OwningCharacter->GetActorLocation().Y;  // Keep Y constant

		// Set the new adjusted location after sliding
		OwningCharacter->SetActorLocation(AdjustedLocation);
	}

	// If the surface is not climbable (e.g., a flat wall), you can stop the movement or trigger a fall/fail state
	if (FMath::Abs(HitResult.Normal.Z) < 0.1f)
	{
		// Optional: Stop movement or handle a "failed climb" scenario
	}
}

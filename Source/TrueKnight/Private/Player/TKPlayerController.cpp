// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TKPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Input/TKInputComponent.h"
#include "UI/Widget/DamageTextComponent.h"

ATKPlayerController::ATKPlayerController()
{
	bReplicates = true;
	
	const FTKGameplayTags& GameplayTags = FTKGameplayTags::Get();

	TagsToIgnore.AddTag(GameplayTags.Abilities_Attack);
	TagsToIgnore.AddTag(GameplayTags.CombatTag_Casting);
	TagsToIgnore.AddTag(GameplayTags.EventTag_Wall);
}

void ATKPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	/*if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		// To create a component, we have to declare a NewObject and then register it (this is normally done by CreateDefaultSubobject)
		// We set the Outer to the TargetCharacter because we are attaching the widget component to it.
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		// First, we attach the component to the target, so it has an initial location, and then we detach it so it can play its own animation
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}*/

	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		// Create the damage text component only on the local client
		if (GetNetMode() != NM_DedicatedServer) // Ensure we're not running on the server (already but double-checking)
		{
			UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
			DamageText->RegisterComponent();
    
			// Attach the component to the target's root component (Z and X movement only)
			FVector AttachLocation = TargetCharacter->GetActorLocation();
    
			// Modify AttachLocation to ensure it aligns to 2D (keep Y axis constant)
			AttachLocation.Y = 20.f;  // Set Y to 0 to keep it in the 2D plane
			DamageText->SetWorldLocation(AttachLocation);
    
			// Set relative rotation to keep it flat in the 2D space (facing the camera or flat on the screen)
			FRotator FlatRotation(0.f, 0.f, 0.f);  // Flat rotation facing forward in 2D
			DamageText->SetWorldRotation(FlatRotation);
			DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
		}
	}
}

void ATKPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TKContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(TKContext, 0);
	}

	bShowMouseCursor = false;

	const FInputModeGameAndUI InputModeData;
	SetInputMode(InputModeData);
}

void ATKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const FTKGameplayTags& GameplayTags = FTKGameplayTags::Get();

	UTKInputComponent* TKInputComponent = CastChecked<UTKInputComponent>(InputComponent);
	
	TKInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	TKInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

	//TODO: Bind the LocalInputConfirm and LocalInputCancel from the ASC
}

void ATKPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// We check if the ASC has any ignored tags to avoid moving during the attack animation.
	// This is only done with functions like Move and Input_Jump that aren't gameplay abilities.
	if (GetASC() && GetASC()->HasAnyMatchingGameplayTags(TagsToIgnore)) return;

	//Movement for 3D/2D Hybrid
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
		const FRotator Rotation = ControlledPawn->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
	//Movement for 2D
	//TODO Create a bool to change from 2D movement to 3D
	/*if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// We set the controller rotation according to the direction of movement
		if (InputActionValue.GetMagnitude() > 0.f)
		{
			SetControlRotation(FRotator(0.f, 0.f, 0.f));
		}
		if (InputActionValue.GetMagnitude() < 0.f)
		{
			SetControlRotation(FRotator(0.f, 180.f, 0.f));
		}
		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f), InputActionValue.GetMagnitude());
	}*/
}

void ATKPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Orange, *InputTag.ToString());
}

void ATKPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ATKPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UTKAbilitySystemComponent* ATKPlayerController::GetASC()
{
	if (!TKAbilitySystemComponent)
	{
		TKAbilitySystemComponent = Cast<UTKAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return TKAbilitySystemComponent;
}

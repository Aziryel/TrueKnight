// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TKPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Input/TKInputComponent.h"

ATKPlayerController::ATKPlayerController()
{
	const FTKGameplayTags& GameplayTags = FTKGameplayTags::Get();

	TagsToIgnore.AddTag(GameplayTags.CombatTag_Attacking);
	TagsToIgnore.AddTag(GameplayTags.CombatTag_Casting);
	TagsToIgnore.AddTag(GameplayTags.EventTag_Wall);
}

void ATKPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TKContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(TKContext, 0);
	}

	bShowMouseCursor = false;

	FInputModeGameAndUI InputModeData;
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
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// We set the controller rotation according to the direction of movement
		if (InputActionValue.GetMagnitude() > 0.f)
		{
			SetControlRotation(FRotator(0.f, 0.f, 0.f));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Emerald, FString::Printf(TEXT("Move Input Value: %f"), InputActionValue.GetMagnitude()));
		}
		if (InputActionValue.GetMagnitude() < 0.f)
		{
			SetControlRotation(FRotator(0.f, 180.f, 0.f));
		}
		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f), InputActionValue.GetMagnitude());
	}
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

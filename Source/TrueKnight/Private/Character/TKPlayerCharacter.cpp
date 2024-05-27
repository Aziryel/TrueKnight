// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/TKTargetInterface.h"
#include "Player/TKPlayerController.h"
#include "Player/TKPlayerState.h"
#include "UI/HUD/TKHUD.h"

ATKPlayerCharacter::ATKPlayerCharacter()
{
	// Setup the Spring Arm and the Camera to be used for a 2D Game
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	FRotator DesiredRotation = FRotator(0.0f, -90.0f, 0.0f);
	SpringArm->SetWorldRotation(DesiredRotation);
	SpringArm->bDoCollisionTest = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATKPlayerCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddUniqueDynamic(this, &ATKPlayerCharacter::OnEndOverlap);
	
}

void ATKPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the server (for standalone game is enough)
	InitAbilityActorInfo();
	
}

void ATKPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATKPlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor) return;

	//ThisActor is declared as TScriptInterface instead of making a cast to the ITKTargetInterface
	ThisActor = OtherActor;
	//Only activate the TargetInterface if the OtherActor has it
	if (ThisActor)
	{
		ThisActor->HighlightActor();
	}
}

void ATKPlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!OtherActor) return;
	
	ThisActor = OtherActor;
	//Only activate the TargetInterface if the OtherActor has it
	if (ThisActor)
	{
		ThisActor->UnhighlightActor();
	}
}

void ATKPlayerCharacter::InitAbilityActorInfo()
{
	ATKPlayerState* TKPlayerState = GetPlayerState<ATKPlayerState>();
	check(TKPlayerState);
	AbilitySystemComponent = TKPlayerState->GetAbilitySystemComponent();
	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->InitAbilityActorInfo(TKPlayerState, this);
	AttributeSet = TKPlayerState->GetAttributeSet();

	//Only continue if the PlayerController is valid
	if (ATKPlayerController* TKPlayerController = Cast<ATKPlayerController>(GetController()))
	{
		if (ATKHUD* TKHUD = Cast<ATKHUD>(TKPlayerController->GetHUD()))
		{
			TKHUD->InitOverlay(TKPlayerController, TKPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

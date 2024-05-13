// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	
}

void ATKPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

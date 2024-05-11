// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TKPlayerController.h"
#include "EnhancedInputSubsystems.h"

ATKPlayerController::ATKPlayerController()
{
	
}

void ATKPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TKContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(TKContext, 0);

	bShowMouseCursor = false;

	FInputModeGameAndUI InputModeData;
	SetInputMode(InputModeData);
}

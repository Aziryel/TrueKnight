// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/TKWidgetController.h"

void UTKWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UTKWidgetController::BroadcastInitialValues()
{
}

void UTKWidgetController::BindCallbacksToDependencies()
{
}

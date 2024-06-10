// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TKHUD.h"

#include "UI/Widget/TKUserWidget.h"
#include "UI/WidgetController/TKAttributeMenuWidgetController.h"
#include "UI/WidgetController/TKOverlayWidgetController.h"

UTKOverlayWidgetController* ATKHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	//Getter to construct it for the first time only
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UTKOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	
	return OverlayWidgetController;
}

UTKAttributeMenuWidgetController* ATKHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UTKAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	
	return AttributeMenuWidgetController;
}

void ATKHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, please fill out BP_TKHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, please fill out BP_TKHUD"));
	
	//We have to include the TKUserWidget.h for it to recognize out of the UUserWidget
	UUserWidget* Widget = CreateWidget<UUserWidget>(PC, OverlayWidgetClass);
	OverlayWidget = Cast<UTKUserWidget>(Widget);

	//Create the WidgetController for the first time
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UTKOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	//Use the WidgetController to set it in the OverlayWidget
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}

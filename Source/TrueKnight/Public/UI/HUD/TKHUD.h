// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TKHUD.generated.h"

class UTKInventoryMenuWidgetController;
class UTKAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UTKOverlayWidgetController;
class UTKUserWidget;

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API ATKHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTKUserWidget> OverlayWidget;

	UTKOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UTKAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	UTKInventoryMenuWidgetController* GetInventoryMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTKUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTKOverlayWidgetController> OverlayWidgetController;
	UPROPERTY()
	TObjectPtr<UTKAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY()
	TObjectPtr<UTKInventoryMenuWidgetController> InventoryMenuWidgetController;

	/*
	 * Classes to create the widget controllers
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTKOverlayWidgetController> OverlayWidgetControllerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTKAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTKInventoryMenuWidgetController> InventoryMenuWidgetControllerClass;
	
};

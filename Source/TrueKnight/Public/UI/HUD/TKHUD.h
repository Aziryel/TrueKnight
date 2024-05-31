// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TKHUD.generated.h"

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

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTKUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UTKOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTKOverlayWidgetController> OverlayWidgetControllerClass;
	
};

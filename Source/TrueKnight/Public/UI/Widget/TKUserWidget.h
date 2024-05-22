// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TKUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKUserWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	//This function is associated with the WidgetController to call it in response of setting the WidgetController
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};

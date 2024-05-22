// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/TKUserWidget.h"

void UTKUserWidget::SetWidgetController(UObject* InWidgetController)
{
	//The WidgetController will be set just before calling the WidgetControllerSet
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAbilitySystemBlueprintLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/TKPlayerState.h"
#include "UI/HUD/TKHUD.h"
#include "UI/WidgetController/TKWidgetController.h"

UTKOverlayWidgetController* UTKAbilitySystemBlueprintLibrary::GetOverlayWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ATKHUD* TKHUD = Cast<ATKHUD>(PC->GetHUD()))
		{
			ATKPlayerState* PS = PC->GetPlayerState<ATKPlayerState>();
			if (PS)
			{
				UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
				UAttributeSet* AS = PS->GetAttributeSet();

				const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

				return TKHUD->GetOverlayWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}

UTKAttributeMenuWidgetController* UTKAbilitySystemBlueprintLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ATKHUD* TKHUD = Cast<ATKHUD>(PC->GetHUD()))
		{
			ATKPlayerState* PS = PC->GetPlayerState<ATKPlayerState>();
			if (PS)
			{
				UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
				UAttributeSet* AS = PS->GetAttributeSet();

				const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

				return TKHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}

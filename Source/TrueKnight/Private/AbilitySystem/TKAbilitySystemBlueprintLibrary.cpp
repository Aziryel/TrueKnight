// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TKAbilitySystemBlueprintLibrary.h"

#include "TKAbilityTypes.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "Game/TKGameModeBase.h"
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

UTKInventoryMenuWidgetController* UTKAbilitySystemBlueprintLibrary::GetInventoryMenuWidgetController(
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

				return TKHUD->GetInventoryMenuWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}

void UTKAbilitySystemBlueprintLibrary::AddItemToInventory(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayEffect> GameplayEffectClass, const float Level,
                                                          const int32 Quantity)
{
	// We return if the Ability System Component or the Gameplay Effect are null
	if (!AbilitySystemComponent || !GameplayEffectClass) return;
	
	// Create a spec handle for the gameplay effect
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, AbilitySystemComponent->MakeEffectContext());
	if (SpecHandle.IsValid())
	{
		// Set the initial quantity
		SpecHandle.Data->SetStackCount(Quantity);

		// Apply the spec to the target
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UTKAbilitySystemBlueprintLibrary::RemoveItemFromInventory(UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayTag ItemTag, int32 Quantity)
{
	if (!AbilitySystemComponent) return;
	
	if (UTKAbilitySystemComponent* TKASC = Cast<UTKAbilitySystemComponent>(AbilitySystemComponent))
	{
		TKASC->RemoveItemFromInventory(ItemTag, Quantity);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The AbilitySystemComponent to remove an item is not of the class TKAbilitySystemComponent"));
	}
	
}

void UTKAbilitySystemBlueprintLibrary::InitializeDefaultsAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.BaseAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UTKAbilitySystemBlueprintLibrary::GiveStartupAbilitites(const UObject* WorldContextObject,
	UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UTKAbilitySystemBlueprintLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ATKGameModeBase* TKGameMode = Cast<ATKGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!TKGameMode) return nullptr;

	return TKGameMode->CharacterClassInfo;
}

bool UTKAbilitySystemBlueprintLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FTKGameplayEffectContext* TKEffectContext = static_cast<const FTKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return TKEffectContext->IsBlockedHit();
	}
	return false;
}

bool UTKAbilitySystemBlueprintLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FTKGameplayEffectContext* TKEffectContext = static_cast<const FTKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return TKEffectContext->IsCriticalHit();
	}
	return false;
}

void UTKAbilitySystemBlueprintLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FTKGameplayEffectContext* TKEffectContext = static_cast<FTKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		TKEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UTKAbilitySystemBlueprintLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FTKGameplayEffectContext* TKEffectContext = static_cast<FTKGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		TKEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

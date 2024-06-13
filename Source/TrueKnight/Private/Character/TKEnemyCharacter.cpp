// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKEnemyCharacter.h"

#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/TKUserWidget.h"

ATKEnemyCharacter::ATKEnemyCharacter()
{
	//Create the TKASC for the enemy character.
	AbilitySystemComponent = CreateDefaultSubobject<UTKAbilitySystemComponent>("AbilitySystemComponent");

	//Create the TKAttributeSet for the enemy character.
	AttributeSet = CreateDefaultSubobject<UTKAttributeSet>("AttributeSet");
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetSprite()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetSprite()->SetGenerateOverlapEvents(true);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ATKEnemyCharacter::HighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Highligh Actor: %s"), *GetNameSafe(this)));
}

void ATKEnemyCharacter::UnhighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("Unhighligh Actor: %s"), *GetNameSafe(this)));
}

int32 ATKEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void ATKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();

	if (UTKUserWidget* TKUserWidget = Cast<UTKUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		TKUserWidget->SetWidgetController(this);
	}
	
	// Bind to delegates from the AbilitySystemComponent

	if (const UTKAttributeSet* TKAS = Cast<UTKAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TKAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChange.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TKAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChange.Broadcast(Data.NewValue);
			}
		);

		OnHealthChange.Broadcast(TKAS->GetHealth());
		OnMaxHealthChange.Broadcast(TKAS->GetMaxHealth());
	}
}

void ATKEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

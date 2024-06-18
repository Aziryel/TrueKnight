// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKEnemyCharacter.h"

#include "PaperFlipbookComponent.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

void ATKEnemyCharacter::Die_Implementation()
{
	SetLifeSpan(LifeSpan);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Die Enemy")));

	Super::Die_Implementation();
}

void ATKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();
	UTKAbilitySystemBlueprintLibrary::GiveStartupAbilitites(this, AbilitySystemComponent);

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
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FTKGameplayTags::Get().EffectTag_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ATKEnemyCharacter::HitReactTagChanged
		);

		OnHealthChange.Broadcast(TKAS->GetHealth());
		OnMaxHealthChange.Broadcast(TKAS->GetMaxHealth());
	}
}

void ATKEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void ATKEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void ATKEnemyCharacter::InitializeDefaultAttributes() const
{
	UTKAbilitySystemBlueprintLibrary::InitializeDefaultsAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

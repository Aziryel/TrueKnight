// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TKEnemyCharacter.h"

#include "PaperFlipbookComponent.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TKAbilitySystemComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "AI/TKAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
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

	// Constrain character movement to the X and Z axis only
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));  // Constrains to the XZ plane
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 10.f, 0.f));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	// Create the Perception Component
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// Create and configure the Sight sense
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// Add the Sight sense to the Perception Component
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	// Create and configure the Hearing sense
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 1500.0f;
	HearingConfig->SetMaxAge(2.0f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// Add the Hearing sense to the Perception Component
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	
	// Bind the perception updated delegate to a function
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATKEnemyCharacter::OnPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATKEnemyCharacter::OnTargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ATKEnemyCharacter::OnTargetPerceptionForgotten);
	
}

void ATKEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!HasAuthority()) return;
	TKAIController = Cast<ATKAIController>(NewController);
	TKAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	TKAIController->RunBehaviorTree(BehaviorTree);
	TKAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	if (CharacterClass == ECharacterClass::Mage || CharacterClass == ECharacterClass::Marksman)
	{
		TKAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), true);
	}
}

void ATKEnemyCharacter::HighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Highligh Actor: %s"), *GetNameSafe(this)));
}

void ATKEnemyCharacter::UnhighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("Unhighligh Actor: %s"), *GetNameSafe(this)));
}

void ATKEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ATKEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

int32 ATKEnemyCharacter::GetPlayerLevel_Implementation()
{
	return Level;
}

void ATKEnemyCharacter::Die_Implementation(const float DyingLifeSpan)
{
	SetLifeSpan(DyingLifeSpan);
	HealthBar->SetVisibility(false);
	TKAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), true);

	Super::Die_Implementation(DyingLifeSpan);
}

void ATKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UTKAbilitySystemBlueprintLibrary::GiveStartupAbilitites(this, AbilitySystemComponent, CharacterClass);
	}

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
	if (TKAIController && TKAIController->GetBlackboardComponent())
	{
		TKAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ATKEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void ATKEnemyCharacter::InitializeDefaultAttributes() const
{
	UTKAbilitySystemBlueprintLibrary::InitializeDefaultsAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void ATKEnemyCharacter::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	
}

void ATKEnemyCharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!TKAIController || !TKAIController->GetBlackboardComponent() || Actor->Tags.Contains(FName("Enemy")))
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		// Actor has been successfully sensed (e.g., seen by sight sense)
		TKAIController->GetBlackboardComponent()->SetValueAsObject(FName("TargetToFollow"), Actor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Following Actor: %s"), *GetNameSafe(Actor)));
	}
}

void ATKEnemyCharacter::OnTargetPerceptionForgotten(AActor* ForgottenActor)
{
	TKAIController->GetBlackboardComponent()->ClearValue(FName("TargetToFollow"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Forgotten Actor: %s."), *GetNameSafe(ForgottenActor)));
}

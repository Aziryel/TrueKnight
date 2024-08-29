// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Character/TKCharacterBase.h"
#include "Interaction/TKTargetInterface.h"
#include "UI/WidgetController/TKOverlayWidgetController.h"
#include "TKEnemyCharacter.generated.h"

struct FAIStimulus;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;
class UWidgetComponent;
class UBehaviorTree;
class ATKAIController;

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API ATKEnemyCharacter : public ATKCharacterBase, public ITKTargetInterface
{
	GENERATED_BODY()

public:
	ATKEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;

	/* Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	/* End Enemy Interface */

	/* Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die_Implementation(const float DyingLifeSpan) override;
	/* End Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChange;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 0.1f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Fighter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ATKAIController> TKAIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* ForgottenActor);
	
};

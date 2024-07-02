// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "TKGameplayTags.h"
#include "AbilitySystem/TKAttributeSet.h"

// Struct to be used locally only
struct TKDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	TKDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTKAttributeSet, BlockChance, Target, false);	
	}
};

static const TKDamageStatics& DamageStatics()
{
	static TKDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather tags from Source and Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set By Caller magnitude
	float TrueDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_TrueDamage);
	float PhysicalDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Physical);
	float MagicDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Magic);
	float FireDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Fire);
	float ColdDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Cold);
	float LightningDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Lightning);
	float PoisonDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Poison);
	float HolyDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Holy);
	float DarkDamage = Spec.GetSetByCallerMagnitude(FTKGameplayTags::Get().DamageType_Dark);
	float TotalDamage = 0.f;

	// Add the True Damage to the total damage
	TotalDamage += TrueDamage;
	
	if (PhysicalDamage > 0.f)
	{
		// Capture BlockChance on Target and determine if there was a successful block
		// If Block, halve the damage
		float TargetBlockChance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
		TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

		const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
		PhysicalDamage = bBlocked ? PhysicalDamage / 2.f : PhysicalDamage;

		TotalDamage += PhysicalDamage;
	}
	if (MagicDamage > 0.f)
	{
		TotalDamage += MagicDamage;
	}
	if (FireDamage > 0.f)
	{
		TotalDamage += FireDamage;
	}
	if (ColdDamage > 0.f)
	{
		TotalDamage += ColdDamage;
	}
	if (LightningDamage > 0.f)
	{
		TotalDamage += LightningDamage;
	}
	if (PoisonDamage > 0.f)
	{
		TotalDamage += PoisonDamage;
	}
	if (HolyDamage > 0.f)
	{
		TotalDamage += HolyDamage;	
	}
	if (DarkDamage > 0.f)
	{
		TotalDamage += DarkDamage;
	}
	

	//if (bBlocked) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("Blocked! Damage: %f"), Damage));
	
	// Add the damage set by caller to the meta-attribute IncomingDamage
	const FGameplayModifierEvaluatedData EvaluatedData(UTKAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, TotalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TKEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

/*#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Components/SphereComponent.h"*/

ATKEffectActor::ATKEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void ATKEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATKEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//This function uses the interface to look for ASC but if not it looks for the ASC in the actor in case the actor doesn't have the interface
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	//If the GameplayEffectClass is not set we crash
	check(GameplayEffectClass);
	//The context is whatever makes the gameplay effect unique. Lightweight wrapper that stores the actual effect context as a pointer "Data".
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	//Try to keep the "Handle" in the name to be descriptive
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void ATKEffectActor::OnOverlap(AActor* TargetActor)
{
	
}

void ATKEffectActor::OnEndOverlap(AActor* TargetActor)
{
	
}



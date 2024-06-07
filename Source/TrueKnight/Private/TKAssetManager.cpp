// Fill out your copyright notice in the Description page of Project Settings.


#include "TKAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "TKGameplayTags.h"

UTKAssetManager& UTKAssetManager::Get()
{
	check(GEngine);
	
	UTKAssetManager* TKAssetManager = Cast<UTKAssetManager>(GEngine->AssetManager);
	return *TKAssetManager;
}

void UTKAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FTKGameplayTags::InitializeNativeGameplayTags();
	
	// We MUST call this to initialize TargetData among other things
	UAbilitySystemGlobals::Get().InitGlobalData();
}

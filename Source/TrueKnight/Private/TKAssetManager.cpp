// Fill out your copyright notice in the Description page of Project Settings.


#include "TKAssetManager.h"

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
}

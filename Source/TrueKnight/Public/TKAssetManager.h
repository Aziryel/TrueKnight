// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TKAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UTKAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UTKAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};

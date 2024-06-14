// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InventoryInfo.generated.h"

class UPaperSprite;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FTKInventoryInfo
{
	GENERATED_BODY()

	// Tag to link to attributes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ItemTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemDescription = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite* ItemSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> ItemEffects;

	// This is not editable because we only want ot change it after an item quantity changes and not manually.
	UPROPERTY(BlueprintReadOnly)
	int32 ItemQuantity = 0;
};

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UInventoryInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	FTKInventoryInfo FindInventoryInfoForTag(const FGameplayTag& ItemTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTKInventoryInfo> InventoryInformation;
};

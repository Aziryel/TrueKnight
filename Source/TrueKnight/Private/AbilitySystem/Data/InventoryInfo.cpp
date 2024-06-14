// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/InventoryInfo.h"

FTKInventoryInfo UInventoryInfo::FindInventoryInfoForTag(const FGameplayTag& ItemTag, bool bLogNotFound) const
{
	for (const FTKInventoryInfo& Info : InventoryInformation)
	{
		if (Info.ItemTag.MatchesTagExact(ItemTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for ItemTag [%s] on InventoryInfo [%s]"), *ItemTag.ToString(), *GetNameSafe(this));
	}

	return FTKInventoryInfo();
}

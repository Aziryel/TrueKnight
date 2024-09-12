// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
namespace EPlayAnimationResult
{
	enum Type
	{
		Completed UMETA(DisplayName = "Completed"),
		Canceled UMETA(DisplayName = "Canceled")
	};
}

#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1
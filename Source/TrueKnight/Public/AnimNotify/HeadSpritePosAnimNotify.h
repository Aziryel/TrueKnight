// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "HeadSpritePosAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class TRUEKNIGHT_API UHeadSpritePosAnimNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

protected:

	// Optionally, a default base offset if needed:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets")
	FVector DefaultOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|RightSide")
	FVector SideRightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|LeftSide")
	FVector SideLeftOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|RightSide")
	FVector DownDiagRightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|RightSide")
	FVector UpDiagRightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|Up")
	FVector DownOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|Down")
	FVector UpOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|LeftSide")
	FVector DownDiagLeftOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offsets|LeftSide")
	FVector UpDiagLeftOffset;
	
};

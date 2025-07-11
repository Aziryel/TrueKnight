// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/HeadSpritePosAnimNotify.h"

#include "PaperFlipbookComponent.h"
#include "Character/TKPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UHeadSpritePosAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (const ATKPlayerCharacter* TKPlayer = Cast<ATKPlayerCharacter>(OwningInstance->GetPaperCharacter()))
	{
		const FRotator CapsuleRot = TKPlayer->GetCapsuleComponent()->GetComponentRotation();
		float Yaw = CapsuleRot.Yaw;

		// Normalize the yaw to the range -180 to 180
		Yaw = UKismetMathLibrary::NormalizeAxis(Yaw);

		// Round to nearest 45 degrees. This will yield one of: -180, -135, -90, -45, 0, 45, 90, 135, or 180 (with 180 and -180 being equivalent).
		float RoundedYaw = FMath::RoundToFloat(Yaw / 45.f) * 45.f;
		RoundedYaw = UKismetMathLibrary::NormalizeAxis(RoundedYaw);

		FVector DirectionalOffset = DefaultOffset;

		if (FMath::IsNearlyEqual(RoundedYaw, 0.f, 1.0f))
        {
            DirectionalOffset = SideRightOffset;
        }
        else if (FMath::IsNearlyEqual(RoundedYaw, 45.f, 1.0f))
        {
            DirectionalOffset = DownDiagRightOffset;
        }
        else if (FMath::IsNearlyEqual(RoundedYaw, -45.f, 1.0f))
        {
            DirectionalOffset = UpDiagRightOffset;
        }
        else if (FMath::IsNearlyEqual(RoundedYaw, 90.f, 1.0f))
        {
            DirectionalOffset = DownOffset;
        }
        else if (FMath::IsNearlyEqual(RoundedYaw, -90.f, 1.0f))
        {
            DirectionalOffset = UpOffset;
        }
        else if (FMath::IsNearlyEqual(RoundedYaw, 135.f, 1.0f))
        {
            DirectionalOffset = DownDiagLeftOffset;
        }
        else if (FMath::IsNearlyEqual(RoundedYaw, -135.f, 1.0f))
        {
            DirectionalOffset = UpDiagLeftOffset;
        }
        else if (FMath::IsNearlyEqual(FMath::Abs(RoundedYaw), 180.f, 1.0f))
        {
            DirectionalOffset = SideLeftOffset;
        }

		TKPlayer->GetHeadSprite()->SetRelativeLocation(TKPlayer->BaseHeadLocation + DirectionalOffset);
		
	}
}

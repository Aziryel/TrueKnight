// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TKEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Components/SphereComponent.h"

ATKEffectActor::ATKEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	SetRootComponent(Sprite);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

}

void ATKEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO Change this to apply gameplay effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UTKAttributeSet* TKAttributeSet = Cast<UTKAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UTKAttributeSet::StaticClass()));
		
		UTKAttributeSet* MutableTKAttributeSet = const_cast<UTKAttributeSet*>(TKAttributeSet);
		MutableTKAttributeSet->SetHealth(TKAttributeSet->GetHealth() + 25.f);
		MutableTKAttributeSet->SetMana(TKAttributeSet->GetMana() + 20.f);
		MutableTKAttributeSet->SetStamina(TKAttributeSet->GetStamina() + 15.f);
		Destroy();
	}
}

void ATKEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ATKEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATKEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ATKEffectActor::OnEndOverlap);
}



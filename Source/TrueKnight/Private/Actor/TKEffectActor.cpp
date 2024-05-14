// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TKEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/TKAttributeSet.h"
#include "Components/SphereComponent.h"

ATKEffectActor::ATKEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

}

void ATKEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO Change this to apply gameplay effect
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UTKAttributeSet* TKAttributeSet = Cast<UTKAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UTKAttributeSet::StaticClass()));
		
		UTKAttributeSet* MutableTKAttributeSet = const_cast<UTKAttributeSet*>(TKAttributeSet);
		MutableTKAttributeSet->SetHealth(TKAttributeSet->GetHealth() + 25.f);
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



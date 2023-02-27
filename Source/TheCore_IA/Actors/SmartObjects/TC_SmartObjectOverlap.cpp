#include "Actors/SmartObjects/TC_SmartObjectOverlap.h"
#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SphereComponent.h"

ATC_SmartObjectOverlap::ATC_SmartObjectOverlap() : Super()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

void ATC_SmartObjectOverlap::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATC_SmartObjectOverlap::OnComponentBeginOverlap);
}

void ATC_SmartObjectOverlap::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATC_BaseInfected* Infected = Cast<ATC_BaseInfected>(OtherActor);
	if (!Infected)
		return;

	Infected->SetCurrentSmartObject(this);
}

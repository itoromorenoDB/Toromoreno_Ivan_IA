#include "Characters/TC_MinionCharacter.h"
#include "Components/SphereComponent.h"
#include "Controllers/TC_MinionController.h"
#include "TheCore_IACharacter.h"

ATC_MinionCharacter::ATC_MinionCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(200.f);

}

void ATC_MinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATC_MinionCharacter::OnSphereOverlapped);
	}
	
}

void ATC_MinionCharacter::OnSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ATheCore_IACharacter>())
	{
		if (ATC_MinionController* MyController = Cast<ATC_MinionController>(GetController()))
		{
			MyController->ChangeFSMState(EState::AttackTarget);
		}
	}
}

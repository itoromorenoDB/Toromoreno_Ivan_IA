#include "Characters/TC_MinionCharacter.h"
#include "Components/SphereComponent.h"
#include "TheCore_IACharacter.h"
#include "Controllers/TC_MinionController.h"
#include "Interfaces/TC_DamageableInterface.h"

ATC_MinionCharacter::ATC_MinionCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(200.0f);
}

float ATC_MinionCharacter::PlayPunchAnimation()
{
	if(!Punch)
		return 0.0f;
	return PlayAnimMontage(Punch);
}

FGenericTeamId ATC_MinionCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(static_cast<uint8>(CurrentTeam));
}

void ATC_MinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATC_MinionCharacter::OnSphereOverlapped);
	}
	
	SetGenericTeamId(static_cast<uint8>(CurrentTeam));
}

void ATC_MinionCharacter::OnSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ITC_DamageableInterface>(OtherActor))
	{
		if (ATC_MinionController* MyController = Cast<ATC_MinionController>(GetController()))
		{
			MyController->ChangeFSMState(EState::AttackTarget);
		}
	}
}

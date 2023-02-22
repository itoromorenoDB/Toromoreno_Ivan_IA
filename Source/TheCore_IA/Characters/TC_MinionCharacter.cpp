#include "Characters/TC_MinionCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "Components/SphereComponent.h"
#include "Controllers/TC_MinionController.h"
#include "Interfaces/TC_DamageableInterface.h"
#include "TheCore_IACharacter.h"

ATC_MinionCharacter::ATC_MinionCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(100.f);

}

float ATC_MinionCharacter::PlayPunchAnimation()
{
	if (!Punch)
		return 0.f;

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
			MyController->BlackboardComponent->SetValue<UBlackboardKeyType_Bool>("CanAttack", true);
		}
	}
}

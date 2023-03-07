#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SplineComponent.h"
#include "Controllers/Infected/TC_BaseInfectedController.h"
#include <Components/SceneComponent.h>
#include <Components/SphereComponent.h>
#include "TheCore_IACharacter.h"
#include <BehaviorTree/BlackboardComponent.h>

ATC_BaseInfected::ATC_BaseInfected() : Super()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	CurrentTeam = static_cast<uint8>(ETeams::Zombies);
}

void ATC_BaseInfected::ResetSmartObject()
{
	SetCurrentSmartObject(MainSmartObject);
}

void ATC_BaseInfected::SetCurrentSmartObject(ATC_SmartObjectBase* NewSmartObject)
{
	CurrentSmartObject = NewSmartObject;
	OnSmartObjectChanged.ExecuteIfBound(CurrentSmartObject);
}

void ATC_BaseInfected::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentSmartObject)
	{
		MainSmartObject = CurrentSmartObject;
	}

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATC_BaseInfected::OnAttackAreaOverlapped);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ATC_BaseInfected::OnAttackAreaOverlappedEnded);
}

void ATC_BaseInfected::OnAttackAreaOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetCanAttack(OtherActor, true);
}

void ATC_BaseInfected::OnAttackAreaOverlappedEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetCanAttack(OtherActor, false);
}

void ATC_BaseInfected::SetCanAttack(AActor* ActorToAttack, bool bCanAttack)
{
	if (!ActorToAttack->IsA<ATheCore_IACharacter>())
		return;

	ATC_BaseInfectedController* MyController = Cast<ATC_BaseInfectedController>(GetController());
	if (!MyController)
		return;

	MyController->BlackboardComponent->SetValueAsBool("CanAttack", bCanAttack);
}

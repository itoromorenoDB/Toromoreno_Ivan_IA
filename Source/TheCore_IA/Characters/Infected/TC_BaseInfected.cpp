#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SplineComponent.h"
#include "Controllers/Infected/TC_BaseInfectedController.h"
#include <Components/SceneComponent.h>
#include <Components/SphereComponent.h>
#include "TheCore_IACharacter.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Actors/TC_Projectile.h"

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

void ATC_BaseInfected::Shoot()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<ATC_Projectile>(ProjectileToSpawn, GetActorTransform(), Params);
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
	ATC_BaseInfectedController* MyController = Cast<ATC_BaseInfectedController>(GetController());
	if (!MyController)
		return;

	MyController->ManageAttack();
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

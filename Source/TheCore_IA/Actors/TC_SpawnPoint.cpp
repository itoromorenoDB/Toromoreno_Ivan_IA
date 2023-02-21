#include "Actors/TC_SpawnPoint.h"
#include "Controllers/TC_MinionController.h"

ATC_SpawnPoint::ATC_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATC_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnMinion();
	//GetWorldTimerManager().SetTimer(SpawnTimer, this, &ATC_SpawnPoint::SpawnMinion, 10.f, true);
}

void ATC_SpawnPoint::SpawnMinion()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ATC_MinionCharacter* SpawnedMinion = GetWorld()->SpawnActor<ATC_MinionCharacter>(ClassToSpawn, GetActorTransform(), Params);
	if (!SpawnedMinion)
	{
		UE_LOG(LogTemp, Error, TEXT("ATC_SpawnPoint::SpawnMinion Couldn't spawn a minion"));
		return;
	}

	SpawnedMinion->SpawnDefaultController();
	SpawnedMinion->CurrentTeam = CurrentTeam;
	ATC_MinionController* MinionController = Cast<ATC_MinionController>(SpawnedMinion->GetController());
	if (MinionController)
	{
		MinionController->SetTarget(Target);
		MinionController->InitFSM();
	}
}
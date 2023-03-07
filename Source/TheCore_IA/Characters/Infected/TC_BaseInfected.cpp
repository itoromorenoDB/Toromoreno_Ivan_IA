#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SplineComponent.h"
#include "Controllers/Infected/TC_BaseInfectedController.h"

ATC_BaseInfected::ATC_BaseInfected() : Super()
{
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
}

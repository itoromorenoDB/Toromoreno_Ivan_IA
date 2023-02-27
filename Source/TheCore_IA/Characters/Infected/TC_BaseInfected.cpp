#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SplineComponent.h"

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

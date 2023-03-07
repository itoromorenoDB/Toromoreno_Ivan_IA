#include "Actors/SmartObjects/TC_SmartObjectQuiet.h"
#include <Components/SceneComponent.h>

ATC_SmartObjectQuiet::ATC_SmartObjectQuiet() : Super()
{
	PointToLook = CreateDefaultSubobject<USceneComponent>(TEXT("PointToLook"));
	PointToLook->SetupAttachment(RootComponent);
}

void ATC_SmartObjectQuiet::BeginPlay()
{
	Super::BeginPlay();

	if (InitActor.Get())
	{
		InitTransform = InitActor.Get()->GetActorTransform();
	}
	else
	{
		InitTransform = GetActorTransform();
	}
}

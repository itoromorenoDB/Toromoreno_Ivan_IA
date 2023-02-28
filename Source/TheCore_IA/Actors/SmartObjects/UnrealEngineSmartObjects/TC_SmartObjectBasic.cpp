#include "Actors/SmartObjects/UnrealEngineSmartObjects/TC_SmartObjectBasic.h"
#include "Components/SceneComponent.h"
#include "SmartObjectComponent.h"

ATC_SmartObjectBasic::ATC_SmartObjectBasic()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SmartObjectComponent = CreateDefaultSubobject<USmartObjectComponent>(TEXT("SmartObjectComponent"));

	SmartObjectComponent->SetupAttachment(RootComponent);
}
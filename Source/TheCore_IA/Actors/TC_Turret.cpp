#include "Actors/TC_Turret.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ATC_Turret::ATC_Turret()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComponent;
}

FGenericTeamId ATC_Turret::GetGenericTeamId() const
{
	return FGenericTeamId(static_cast<uint8>(CurrentTeam));
}

#include "Actors/TC_Projectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

ATC_Projectile::ATC_Projectile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	BoxComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("UProjectileMovementComponent"));
}



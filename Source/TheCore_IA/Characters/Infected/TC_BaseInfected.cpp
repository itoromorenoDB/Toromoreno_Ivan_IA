#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SplineComponent.h"

ATC_BaseInfected::ATC_BaseInfected()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
#if WITH_EDITOR
	SplineComponent->bDrawDebug = true;
#endif
}

void ATC_BaseInfected::BeginPlay()
{
	Super::BeginPlay();

	FillSplinePoints();
}

void ATC_BaseInfected::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATC_BaseInfected::FillSplinePoints()
{
	for (int32 Index = 0; Index <= SplineComponent->GetNumberOfSplinePoints(); ++Index)
	{
		SplinePoints.Add(SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World));
	}
}

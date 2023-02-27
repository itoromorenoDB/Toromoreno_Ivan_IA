#include "TC_SmartObjectPatrol.h"
#include "Components/SplineComponent.h"

ATC_SmartObjectPatrol::ATC_SmartObjectPatrol() : Super()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

#if WITH_EDITOR
	SplineComponent->bDrawDebug = true;
#endif
}

void ATC_SmartObjectPatrol::FillSplinePoints()
{
	for (int32 Index = 0; Index <= SplineComponent->GetNumberOfSplinePoints(); ++Index)
	{
		SplinePoints.Add(SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World));
	}
}

const TArray<FVector>& ATC_SmartObjectPatrol::GetSplinePoints() const
{
	return SplinePoints;
}

void ATC_SmartObjectPatrol::BeginPlay()
{
	Super::BeginPlay();

	FillSplinePoints();
}
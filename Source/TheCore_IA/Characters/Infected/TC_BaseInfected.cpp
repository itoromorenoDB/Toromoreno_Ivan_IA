#include "Characters/Infected/TC_BaseInfected.h"
#include "Components/SplineComponent.h"

ATC_BaseInfected::ATC_BaseInfected()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

	HearingSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("HearingSplineComponent"));
	HearingSplineComponent->SetupAttachment(RootComponent);

#if WITH_EDITOR
	SplineComponent->bDrawDebug = true;
	HearingSplineComponent->bDrawDebug = true;
#endif
}

void ATC_BaseInfected::BeginPlay()
{
	Super::BeginPlay();

	FillSplinePoints(SplinePoints, SplineComponent);
	FillSplinePoints(HearingSplinePoints, HearingSplineComponent);
}

void ATC_BaseInfected::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATC_BaseInfected::FillSplinePoints(TArray<FVector>& Points, USplineComponent* Spline)
{
	for (int32 Index = 0; Index <= Spline->GetNumberOfSplinePoints(); ++Index)
	{
		Points.Add(Spline->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World));
	}
}

const TArray<FVector>& ATC_BaseInfected::GetSplinePoints() const
{
	return SplinePoints;
}

const TArray<FVector>& ATC_BaseInfected::GetHearingSplinePoints() const
{
	return HearingSplinePoints;
}

#pragma once

#include "CoreMinimal.h"
#include "TC_SmartObjectBase.h"
#include "TC_SmartObjectPatrol.generated.h"

class USplineComponent;

UCLASS()
class THECORE_IA_API ATC_SmartObjectPatrol : public ATC_SmartObjectBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Patrol")
		USplineComponent* SplineComponent = nullptr;

	ATC_SmartObjectPatrol();
	void FillSplinePoints();
	const TArray<FVector>& GetSplinePoints() const;

protected:
	void BeginPlay() override;

private:

	UPROPERTY()
		TArray<FVector> SplinePoints;

};

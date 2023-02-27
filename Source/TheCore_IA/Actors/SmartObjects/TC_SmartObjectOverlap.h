#pragma once

#include "CoreMinimal.h"
#include "Actors/SmartObjects/TC_SmartObjectBase.h"
#include "TC_SmartObjectOverlap.generated.h"

class USphereComponent;

UCLASS()
class THECORE_IA_API ATC_SmartObjectOverlap : public ATC_SmartObjectBase
{
	GENERATED_BODY()

public:

	UPROPERTY(Editanywhere)
		USphereComponent* SphereComponent = nullptr;

	ATC_SmartObjectOverlap();

protected:

	void BeginPlay() override;

private:

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};

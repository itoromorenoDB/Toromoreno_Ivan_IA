#pragma once

#include "CoreMinimal.h"
#include "Actors/SmartObjects/TC_SmartObjectBase.h"
#include "TC_SmartObjectQuiet.generated.h"

class USceneComponent;

UCLASS()
class THECORE_IA_API ATC_SmartObjectQuiet : public ATC_SmartObjectBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TWeakObjectPtr<AActor> InitActor = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* PointToLook = nullptr;

	ATC_SmartObjectQuiet();

	FTransform InitTransform;

	virtual void BeginPlay() override;
	
};

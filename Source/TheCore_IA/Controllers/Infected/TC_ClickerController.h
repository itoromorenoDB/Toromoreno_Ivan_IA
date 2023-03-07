#pragma once

#include "CoreMinimal.h"
#include "Controllers/Infected/TC_BaseInfectedController.h"
#include <Perception/AIPerceptionTypes.h>
#include "TC_ClickerController.generated.h"

UCLASS()
class THECORE_IA_API ATC_ClickerController : public ATC_BaseInfectedController
{
	GENERATED_BODY()

public:

	ATC_ClickerController();

private:

	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
};

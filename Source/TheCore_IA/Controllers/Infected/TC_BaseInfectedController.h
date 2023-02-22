#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TC_BaseInfectedController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;

UCLASS()
class THECORE_IA_API ATC_BaseInfectedController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Sight* SightConfig = nullptr;

	ATC_BaseInfectedController();

protected:

	virtual void OnPossess(APawn* InPawn) override;
	
};

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TC_BaseInfectedController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class ATC_BaseInfected;
class ATC_SmartObjectBase;

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
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Hearing* HearingConfig = nullptr;

	ATC_BaseInfectedController();

protected:

	UPROPERTY()
		ATC_BaseInfected* CurrentAgent = nullptr;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:

	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	template<class T>
	bool IsValidStimulus(FAIStimulus Stimulus)
	{
		return UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == T::StaticClass();
	}

	void SmartObjectChanged(ATC_SmartObjectBase* NewSmartObject);

	void ManageSight(AActor* Actor);
	void ManageHearing(const FVector& HearingLocation);
	
};

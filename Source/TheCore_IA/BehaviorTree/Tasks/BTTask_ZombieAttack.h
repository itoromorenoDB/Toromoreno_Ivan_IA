#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ZombieAttack.generated.h"

class ATC_BaseInfected;

UCLASS()
class THECORE_IA_API UBTTask_ZombieAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public: 

	UBTTask_ZombieAttack();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY()
		TObjectPtr<UBehaviorTreeComponent> MyOwnerComp = nullptr;
	UPROPERTY()
		TObjectPtr<ATC_BaseInfected> MyInfected = nullptr;

	FTimerHandle TimerHandle;

	int32 ComboNumber = 0;
	int32 CurrentComboPlaying = 0;

	void OnTimerFinished();
	
};

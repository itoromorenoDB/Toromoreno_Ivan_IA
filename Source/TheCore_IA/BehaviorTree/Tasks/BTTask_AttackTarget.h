#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackTarget.generated.h"

class UAnimMontage;
class UBehaviorTreeComponent;

UCLASS()
class THECORE_IA_API UBTTask_AttackTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontage = nullptr;
	UBTTask_AttackTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY()
		UBehaviorTreeComponent* BTComponent = nullptr;
	FTimerHandle AnimTimer;
	void OntAnimTimer();

};

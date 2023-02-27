#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ResetSmartObject.generated.h"

UCLASS()
class THECORE_IA_API UBTTask_ResetSmartObject : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ResetSmartObject();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

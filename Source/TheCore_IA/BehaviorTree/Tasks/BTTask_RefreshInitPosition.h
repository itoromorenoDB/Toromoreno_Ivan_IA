#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RefreshInitPosition.generated.h"

UCLASS()
class THECORE_IA_API UBTTask_RefreshInitPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		bool bHasToLook = false;

	UBTTask_RefreshInitPosition();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};

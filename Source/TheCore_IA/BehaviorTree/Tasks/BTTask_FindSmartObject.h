#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindSmartObject.generated.h"

class USmartObjectBehaviorDefinition;

UCLASS()
class THECORE_IA_API UBTTask_FindSmartObject : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<USmartObjectBehaviorDefinition> BehaviorDefinitionClass;

	UBTTask_FindSmartObject();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

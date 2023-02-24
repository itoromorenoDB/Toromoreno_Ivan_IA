#include "BehaviorTree/Tasks/BTTask_ClearBlackboardKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardKey::UBTTask_ClearBlackboardKey() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ClearBlackboardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return EBTNodeResult::Failed;

	BlackboardComponent->ClearValue(BlackboardKey.GetSelectedKeyID());

	return EBTNodeResult::Succeeded;
}

#include "BehaviorTree/Tasks/BTTask_UseSmartObject.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SmartObjectRuntime.h"
#include "BlackboardKeyType_SOClaimHandle.h"

UBTTask_UseSmartObject::UBTTask_UseSmartObject()
{
	bCreateNodeInstance = true;
	NodeName = "Use Smart Object C";
}

EBTNodeResult::Type UBTTask_UseSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
		return EBTNodeResult::Failed;

	const FSmartObjectClaimHandle& ClaimHandle = Blackboard->GetValue<UBlackboardKeyType_SOClaimHandle>(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}


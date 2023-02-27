#include "BehaviorTree/Tasks/BTTask_ResetSmartObject.h"
#include "AIController.h"
#include "Characters/Infected/TC_BaseInfected.h"

UBTTask_ResetSmartObject::UBTTask_ResetSmartObject() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ResetSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	ATC_BaseInfected* BaseInfected = Controller ? Cast<ATC_BaseInfected>(Controller->GetPawn()) : nullptr;
	if (!BaseInfected)
		return EBTNodeResult::Failed;

	BaseInfected->ResetSmartObject();
	
	return EBTNodeResult::Succeeded;
}
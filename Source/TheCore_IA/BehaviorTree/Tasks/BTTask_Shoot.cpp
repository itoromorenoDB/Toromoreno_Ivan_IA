#include "BehaviorTree/Tasks/BTTask_Shoot.h"
#include "Characters/Infected/TC_BaseInfected.h"
#include <AIController.h>

UBTTask_Shoot::UBTTask_Shoot()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	ATC_BaseInfected* Infected = Controller ? Cast<ATC_BaseInfected>(Controller->GetPawn()) : nullptr;
	if (!Infected)
		return EBTNodeResult::Failed;

	Infected->Shoot();

	return EBTNodeResult::Succeeded;
}

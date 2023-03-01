#include "BehaviorTree/Tasks/BTTask_GatherSmartObject.h"
#include "Actors/SmartObjects/TC_SmartObjectBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Infected/TC_BaseInfected.h"

UBTTask_GatherSmartObject::UBTTask_GatherSmartObject()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_GatherSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* Controller = OwnerComp.GetAIOwner();
	ATC_BaseInfected* Infected = Controller ? Cast<ATC_BaseInfected>(Controller->GetPawn()) : nullptr;

	if (!Blackboard || !Infected)
		return EBTNodeResult::Failed;

	ATC_SmartObjectBase* SmartObject = Cast<ATC_SmartObjectBase>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!SmartObject)
		return EBTNodeResult::Failed;

	Infected->SetCurrentSmartObject(SmartObject);

	return EBTNodeResult::Succeeded;
}

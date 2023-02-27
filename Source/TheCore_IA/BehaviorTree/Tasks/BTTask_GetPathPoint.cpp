#include "BehaviorTree/Tasks/BTTask_GetPathPoint.h"
#include "Actors/SmartObjects/TC_SmartObjectPatrol.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Infected/TC_BaseInfected.h"

UBTTask_GetPathPoint::UBTTask_GetPathPoint() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_GetPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AAIController* MyController = OwnerComp.GetAIOwner();
	ATC_BaseInfected* MyInfected = MyController ? Cast<ATC_BaseInfected>(MyController->GetPawn()) : nullptr;

	if (!MyInfected || !BlackboardComponent)
		return EBTNodeResult::Failed;

	ATC_SmartObjectPatrol* SmartObjectPatrol = Cast<ATC_SmartObjectPatrol>(MyInfected->CurrentSmartObject);
	const TArray<FVector>& SplinePoints = SmartObjectPatrol ? SmartObjectPatrol->GetSplinePoints() : TArray<FVector>();
	if (SplinePoints.IsEmpty())
		return EBTNodeResult::Succeeded;

	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(GetSelectedBlackboardKey(), SplinePoints[Index]);

	if (Index < SplinePoints.Num() - 1)
	{
		Index++;
		return EBTNodeResult::Succeeded;
	}

	Index = 0;

	return EBTNodeResult::Succeeded;
}

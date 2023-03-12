#include "BehaviorTree/Tasks/BTTask_AttackTarget.h"
#include "Characters/TC_MinionCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_AttackTarget::UBTTask_AttackTarget() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!AnimMontage)
		return EBTNodeResult::Failed;

	AAIController* MyController = OwnerComp.GetAIOwner();
	ATC_MinionCharacter* MyMinion = MyController ? Cast<ATC_MinionCharacter>(MyController->GetPawn()) : nullptr;
	if (!MyMinion)
		return EBTNodeResult::Failed;

	const float AnimTime = MyMinion->PlayAnimMontage(AnimMontage);
	MyMinion->GetWorldTimerManager().SetTimer(AnimTimer, this, &UBTTask_AttackTarget::OntAnimTimer, AnimTime);
	BTComponent = &OwnerComp;
	return EBTNodeResult::InProgress;
}

void UBTTask_AttackTarget::OntAnimTimer()
{
	FinishLatentTask(*BTComponent, EBTNodeResult::Succeeded);
}

#include "BehaviorTree/Tasks/BTTask_ZombieAttack.h"
#include <AIController.h>
#include "Characters/Infected/TC_BaseInfected.h"
#include <Kismet/KismetMathLibrary.h>

UBTTask_ZombieAttack::UBTTask_ZombieAttack() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	MyInfected = Controller ? Cast<ATC_BaseInfected>(Controller->GetPawn()) : nullptr;
	if (!MyInfected)
		return EBTNodeResult::Failed;

	MyOwnerComp = &OwnerComp;
	ComboNumber = UKismetMathLibrary::RandomIntegerInRange(1, MyInfected->ComboInformation.Attacks.Num());

	const float AnimTime = MyInfected->PlayAnimMontage(MyInfected->ComboInformation.Attacks[CurrentComboPlaying]);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_ZombieAttack::OnTimerFinished, AnimTime, false);

	return EBTNodeResult::InProgress;
}

void UBTTask_ZombieAttack::OnTimerFinished()
{
	++CurrentComboPlaying;
	if (CurrentComboPlaying == ComboNumber)
	{
		CurrentComboPlaying = 0;
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		const float AnimTime = MyInfected->PlayAnimMontage(MyInfected->ComboInformation.Attacks[CurrentComboPlaying]);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_ZombieAttack::OnTimerFinished, AnimTime, false);
	}
}

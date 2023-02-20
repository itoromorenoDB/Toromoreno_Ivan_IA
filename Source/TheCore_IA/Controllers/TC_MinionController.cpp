#include "Controllers/TC_MinionController.h"

ATC_MinionController::ATC_MinionController() : Super()
{
	FSMComponent = CreateDefaultSubobject<UTC_FSMComponent>(TEXT("FSM Component"));
}

AActor* ATC_MinionController::GetTarget() const
{
	return CurrentTarget.IsValid() ? CurrentTarget.Get() : nullptr;
}

void ATC_MinionController::SetTarget(AActor* NewTarget)
{
	if (CurrentTarget.Get() == NewTarget)
		return;

	CurrentTarget = NewTarget;
	TargetChanged.ExecuteIfBound(NewTarget);
}

void ATC_MinionController::InitFSM()
{
	ChangeFSMState(EState::GoToTarget);
}

void ATC_MinionController::ChangeFSMState(EState State)
{
	if (FSMComponent)
	{
		FSMComponent->ChangeState(State);
	}
}

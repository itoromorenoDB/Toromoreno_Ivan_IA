#include "FSM/States/TC_GoToTarget.h"
#include "Controllers/TC_MinionController.h"

void UTC_GoToTarget::OnEnterState()
{
	Super::OnEnterState();

	ATC_MinionController* MinionController = Cast<ATC_MinionController>(GetOwnerController());
	if (!MinionController)
		return;

	CurrentTarget = MinionController->GetTarget();
	AActor* Target = CurrentTarget.Get();
	OnTargetChanged(Target);
	MinionController->TargetChanged.BindUObject(this, &UTC_GoToTarget::OnTargetChanged);
}

void UTC_GoToTarget::OnExitState()
{
	Super::OnExitState();
	OnTargetChanged(nullptr);
	if (ATC_MinionController* MinionController = Cast<ATC_MinionController>(GetOwnerController()))
	{
		MinionController->StopMovement();
	}
}

void UTC_GoToTarget::OnTargetChanged(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
	ATC_MinionController* MinionController = Cast<ATC_MinionController>(GetOwnerController());
	if (!MinionController || !NewTarget)
		return;

	MinionController->MoveTo(NewTarget);
}

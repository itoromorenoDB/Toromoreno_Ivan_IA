#include "FSM/States/TC_AttackTarget.h"
#include "Controllers/TC_MinionController.h"
#include "Characters/TC_MinionCharacter.h"

void UTC_AttackTarget::OnEnterState()
{
	Super::OnEnterState();
	OnAttackTimer();
}

void UTC_AttackTarget::OnExitState()
{
	Super::OnExitState();

	if (AttackTimer.IsValid())
	{
		ATC_MinionController* MyController = Cast<ATC_MinionController>(GetOwnerController());
		ATC_MinionCharacter* MyMinion = MyController ? Cast<ATC_MinionCharacter>(MyController->GetPawn()) : nullptr;

		if (!MyMinion)
			return;

		MyMinion->GetWorldTimerManager().ClearTimer(AttackTimer);
	}
}

void UTC_AttackTarget::OnAttackTimer()
{
	ATC_MinionController* MyController = Cast<ATC_MinionController>(GetOwnerController());
	ATC_MinionCharacter* MyMinion = MyController ? Cast<ATC_MinionCharacter>(MyController->GetPawn()) : nullptr;

	if (!MyMinion)
		return;

	const float PunchDuration = MyMinion->PlayPunchAnimation();
	if (PunchDuration > 0.f)
	{
		MyMinion->GetWorldTimerManager().SetTimer(AttackTimer, this, &UTC_AttackTarget::OnAttackTimer, PunchDuration);
	}
}

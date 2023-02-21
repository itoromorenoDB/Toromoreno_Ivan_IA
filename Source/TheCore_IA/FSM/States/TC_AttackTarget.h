#pragma once

#include "CoreMinimal.h"
#include "FSM/TC_State.h"
#include "TC_AttackTarget.generated.h"

UCLASS()
class THECORE_IA_API UTC_AttackTarget : public UTC_State
{
	GENERATED_BODY()

public:

	void OnEnterState() override;
	void OnExitState() override;

private:

	FTimerHandle AttackTimer;
	void OnAttackTimer();
	
};

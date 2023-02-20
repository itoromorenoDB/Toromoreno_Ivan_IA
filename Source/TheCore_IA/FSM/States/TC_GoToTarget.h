#pragma once

#include "CoreMinimal.h"
#include "FSM/TC_State.h"
#include "TC_GoToTarget.generated.h"

UCLASS()
class THECORE_IA_API UTC_GoToTarget : public UTC_State
{
	GENERATED_BODY()

public:
	void OnEnterState() override;
	void OnExitState() override;

private:
	TWeakObjectPtr<AActor> CurrentTarget = nullptr;

	void OnTargetChanged(AActor* NewTarget);
	
};

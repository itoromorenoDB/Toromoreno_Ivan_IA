#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/TC_FSMComponent.h"
#include "TC_MinionController.generated.h"

DECLARE_DELEGATE_OneParam(FOnTargetChanged, AActor*);

UCLASS()
class THECORE_IA_API ATC_MinionController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		UTC_FSMComponent* FSMComponent = nullptr;

	FOnTargetChanged TargetChanged;

	ATC_MinionController();
	AActor* GetTarget() const;

	void SetTarget(AActor* NewTarget);
	void InitFSM();
	void ChangeFSMState(EState State);

private:
	TWeakObjectPtr<AActor> CurrentTarget = nullptr;
	
};

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/TC_FSMComponents.h"
#include "Characters/TC_MinionCharacter.h"
#include "TC_MinionController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Damage;
class UBehaviorTreeComponent;
class UBlackboardComponent;

DECLARE_DELEGATE_OneParam(FOnTargetChanged, AActor*);

UCLASS()
class THECORE_IA_API ATC_MinionController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		UTC_FSMComponents* FSMComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Sight* ConfigSight = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Damage* ConfigDamage = nullptr;
	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent = nullptr;

	FOnTargetChanged TargetChanged;
	ETeam CurrentTeam = ETeam::None;

	ATC_MinionController();
	AActor* GetTarget() const;
	
	void SetTarget(AActor* NewTarget);
	void InitFSM();
	void ChangeFSMState(EState State);
	FGenericTeamId GetGenericTeamId() const override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	void BeginPlay() override;
	
private:
	TWeakObjectPtr<AActor> CurrentTarget = nullptr;
	TWeakObjectPtr<AActor> MainTarget = nullptr;
	FTimerHandle LostTargetTimer;

	UFUNCTION()
		void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void ReactToSight(AActor* Target);
	void OnLostTarget();

};

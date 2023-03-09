#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IdleBreaker.generated.h"

class UAnimMontage;
class UBehaviorTreeComponent;
class USkeletalMeshComponent;

UCLASS()
class THECORE_IA_API UBTTask_IdleBreaker : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> Animations;

	UBTTask_IdleBreaker();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) override;

private:

	UPROPERTY()
		TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;

	UPROPERTY()
		TObjectPtr<USkeletalMeshComponent> CachedSkelMesh;

	FTimerHandle TimerHandle;
	
	void OnTimerFinished();

};

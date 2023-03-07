#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TC_FSMComponent.generated.h"

class UTC_State;

UENUM(BlueprintType)
enum class EState : uint8
{
	GoToTarget,
	AttackTarget
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THECORE_IA_API UTC_FSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "FSM")
		TMap<EState, TSoftClassPtr<UTC_State>> States;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ChangeState(EState NewState);

protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<UTC_State> CurrentState = nullptr;
};

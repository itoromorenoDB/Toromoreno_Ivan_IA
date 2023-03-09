#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionSystem.h>
#include <BrainComponent.h>
#include "TC_BaseInfectedController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class ATC_BaseInfected;
class ATC_SmartObjectBase;

namespace ATC_BaseInfectedController_Consts
{
	static FName HearingLocationSet = TEXT("HearingLocationSet");
	static FName SightLocationSet = TEXT("SightLocationSet");
	static FName Attacking = TEXT("Attacking");
	constexpr int32 HearingRequestID = 44;
	constexpr int32 SightRequestID = 45;
	constexpr int32 AttackRequestID = 46;
};

UENUM()
enum class ETeams : uint8
{
	Zombies,
	Characters
};

UCLASS()
class THECORE_IA_API ATC_BaseInfectedController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Sight* SightConfig = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Hearing* HearingConfig = nullptr;
	UPROPERTY(EditDefaultsOnly)
		bool bCanUseSight = true;
	ATC_BaseInfectedController();

	virtual FGenericTeamId GetGenericTeamId() const override;
	void ManageAttack();

protected:

	UPROPERTY()
		ATC_BaseInfected* CurrentAgent = nullptr;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	void ManageHearing(const FVector& HearingLocation);
	template<class T>
	bool IsValidStimulus(FAIStimulus Stimulus)
	{
		return UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == T::StaticClass();
	}

private:

	UFUNCTION()
		virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void SmartObjectChanged(ATC_SmartObjectBase* NewSmartObject);

	void ManageSight(AActor* Actor);
	void ManageMsg(FName MessageName, int32 RequestId, FAIMessage::EStatus Status);
	
};

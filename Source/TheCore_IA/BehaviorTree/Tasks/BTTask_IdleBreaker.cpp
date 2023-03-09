#include "BehaviorTree/Tasks/BTTask_IdleBreaker.h"
#include "AIController.h"
#include "Characters/Infected/TC_BaseInfected.h"
#include "Kismet/KismetMathLibrary.h"
#include <Animation/AnimMontage.h>
#include "Controllers/Infected/TC_BaseInfectedController.h"

UBTTask_IdleBreaker::UBTTask_IdleBreaker() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_IdleBreaker::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Animations.IsEmpty())
		return EBTNodeResult::Succeeded;

	AAIController* Controller = OwnerComp.GetAIOwner();
	ATC_BaseInfected* Infected = Controller ? Cast<ATC_BaseInfected>(Controller->GetPawn()) : nullptr;
	MyOwnerComp = &OwnerComp;

	if (!Infected)
		return EBTNodeResult::Failed;

	int32 RandomIndex = UKismetMathLibrary::RandomInteger(Animations.Num());
	UAnimMontage* MontageToPlay = Animations[RandomIndex];

	if (!MontageToPlay)
		return EBTNodeResult::Failed;

	CachedSkelMesh = Infected->GetMesh();
	CachedSkelMesh->PlayAnimation(MontageToPlay, false);
	const float FinishDelay = MontageToPlay->GetPlayLength();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_IdleBreaker::OnTimerFinished, FinishDelay, false);
	WaitForMessage(OwnerComp, ATC_BaseInfectedController_Consts::SightLocationSet, ATC_BaseInfectedController_Consts::SightRequestID);
	WaitForMessage(OwnerComp, ATC_BaseInfectedController_Consts::HearingLocationSet, ATC_BaseInfectedController_Consts::HearingRequestID);
	WaitForMessage(OwnerComp, ATC_BaseInfectedController_Consts::Attacking, ATC_BaseInfectedController_Consts::AttackRequestID);
	return EBTNodeResult::InProgress;
}

void UBTTask_IdleBreaker::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	if (Message == ATC_BaseInfectedController_Consts::HearingLocationSet && ATC_BaseInfectedController_Consts::HearingRequestID || 
		Message == ATC_BaseInfectedController_Consts::SightLocationSet && ATC_BaseInfectedController_Consts::SightRequestID || 
		Message == ATC_BaseInfectedController_Consts::Attacking && ATC_BaseInfectedController_Consts::AttackRequestID)
	{
		CachedSkelMesh->Stop();
		CachedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_IdleBreaker::OnTimerFinished()
{
	CachedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
}

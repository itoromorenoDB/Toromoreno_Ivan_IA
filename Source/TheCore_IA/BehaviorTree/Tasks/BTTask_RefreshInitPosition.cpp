// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Tasks/BTTask_RefreshInitPosition.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "Characters/Infected/TC_BaseInfected.h"
#include "Actors/SmartObjects/TC_SmartObjectQuiet.h"
#include <AIController.h>

UBTTask_RefreshInitPosition::UBTTask_RefreshInitPosition() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_RefreshInitPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AAIController* Controller = OwnerComp.GetAIOwner();
	ATC_BaseInfected* Infected = Controller ? Cast<ATC_BaseInfected>(Controller->GetPawn()) : nullptr;

	if (!BlackboardComponent || !Infected)
		return EBTNodeResult::Failed;

	ATC_SmartObjectQuiet* QuietSmartObject = Cast<ATC_SmartObjectQuiet>(Infected->CurrentSmartObject);
	if (!QuietSmartObject)
	{
		BlackboardComponent->ClearValue("InitPosition");
		return EBTNodeResult::Succeeded;
	}

	if (bHasToLook)
	{
		BlackboardComponent->SetValueAsVector("PointToLook", QuietSmartObject->PointToLook->GetComponentLocation());
	}
	else
	{
		BlackboardComponent->SetValueAsVector("InitPosition", QuietSmartObject->GetActorLocation());
	}
	return EBTNodeResult::Succeeded;
}


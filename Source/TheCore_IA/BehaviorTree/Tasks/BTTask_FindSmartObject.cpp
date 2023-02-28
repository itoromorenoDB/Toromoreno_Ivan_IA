#include "BehaviorTree/Tasks/BTTask_FindSmartObject.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackboardKeyType_SOClaimHandle.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "SmartObjectBlueprintFunctionLibrary.h"
#include "SmartObjectSubsystem.h"

UBTTask_FindSmartObject::UBTTask_FindSmartObject() : Super()
{
	bCreateNodeInstance = true;
	NodeName = "Find Smart Object C";
}

EBTNodeResult::Type UBTTask_FindSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* Controller = OwnerComp.GetAIOwner();
	ACharacter* Character = Controller ? Cast<ACharacter>(Controller->GetPawn()) : nullptr;
	if (!Blackboard || !Character)
		return EBTNodeResult::Failed;

	USmartObjectSubsystem* SmartObjectSubsystem = GetWorld()->GetSubsystem<USmartObjectSubsystem>();
	if (!SmartObjectSubsystem)
		return EBTNodeResult::Failed;

	const FVector& CurrentLocation = Character->GetActorLocation();
	FVector Min = CurrentLocation - FVector(2000.f, 2000.f, 2000.f);
	FVector Max = CurrentLocation + FVector(2000.f, 2000.f, 2000.f);

	TArray<FSmartObjectRequestResult> Results;
	FSmartObjectRequest Request;
	Request.QueryBox = UKismetMathLibrary::MakeBox(Min, Max);
	Request.Filter.BehaviorDefinitionClass = BehaviorDefinitionClass;
	SmartObjectSubsystem->FindSmartObjects(Request, Results);

	if (Results.IsEmpty())
		return EBTNodeResult::Failed;

	const FSmartObjectClaimHandle& ClaimHandle = SmartObjectSubsystem->Claim(Results[0]);
	if (!USmartObjectBlueprintFunctionLibrary::IsValidSmartObjectClaimHandle(ClaimHandle))
		return EBTNodeResult::Failed;

	Blackboard->SetValue<UBlackboardKeyType_SOClaimHandle>(GetSelectedBlackboardKey(), ClaimHandle);

	return EBTNodeResult::Succeeded;

}

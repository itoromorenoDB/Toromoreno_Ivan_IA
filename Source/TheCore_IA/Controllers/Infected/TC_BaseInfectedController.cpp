#include "Controllers/Infected/TC_BaseInfectedController.h"
#include "Actors/SmartObjects/TC_SmartObjectBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Characters/Infected/TC_BaseInfected.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Actors/SmartObjects/TC_SmartObjectQuiet.h"

ATC_BaseInfectedController::ATC_BaseInfectedController() : Super()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject <UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	SightConfig->SightRadius = 300.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 20.f;
	SightConfig->PeripheralVisionAngleDegrees = 45.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;

	PerceptionComponent->ConfigureSense(*HearingConfig);
	PerceptionComponent->ConfigureSense(*SightConfig);

	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

}

FGenericTeamId ATC_BaseInfectedController::GetGenericTeamId() const
{
	ATC_BaseInfected* Infected = Cast<ATC_BaseInfected>(GetPawn());
	return Infected ? FGenericTeamId(Infected->CurrentTeam) : FGenericTeamId();
}

void ATC_BaseInfectedController::BeginPlay()
{
	Super::BeginPlay();

	if (!CurrentAgent)
		return;

	SmartObjectChanged(CurrentAgent->CurrentSmartObject);

	if (ATC_SmartObjectQuiet* Quiet = Cast<ATC_SmartObjectQuiet>(CurrentAgent->CurrentSmartObject))
	{
		BlackboardComponent->SetValueAsVector("InitPosition", Quiet->InitTransform.GetLocation());
	}

}

void ATC_BaseInfectedController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATC_BaseInfected* Infected = Cast<ATC_BaseInfected>(InPawn);
	UBehaviorTree* BehaviorTree = Infected ? Infected->BehaviorTree : nullptr;
	if (BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}

	CurrentAgent = Cast<ATC_BaseInfected>(GetPawn());
	CurrentAgent->OnSmartObjectChanged.BindUObject(this, &ATC_BaseInfectedController::SmartObjectChanged);
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ATC_BaseInfectedController::OnTargetPerceptionUpdated);
}

void ATC_BaseInfectedController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACharacter* InfectedChar = Cast<ACharacter>(GetPawn());
	UCharacterMovementComponent* MovementComp = InfectedChar ? InfectedChar->GetCharacterMovement() : nullptr;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (MovementComp)
		{
			MovementComp->MaxWalkSpeed = 300.f;
		}

		if (IsValidStimulus<UAISense_Sight>(Stimulus) && bCanUseSight)
		{
			ManageSight(Actor);
		}
		else if (IsValidStimulus<UAISense_Hearing>(Stimulus))
		{
			ManageHearing(Stimulus.StimulusLocation);
		}
	}
	else
	{
		if (MovementComp)
		{
			MovementComp->MaxWalkSpeed = 50.f;
		}

		if (bCanUseSight)
		{
			ManageSight(nullptr);
		}

		BlackboardComponent->ClearValue("HearingLocation");
	}
}

void ATC_BaseInfectedController::SmartObjectChanged(ATC_SmartObjectBase* NewSmartObject)
{
	if (NewSmartObject)
	{
		FGameplayTag Subtag;
		BehaviorTreeComponent->SetDynamicSubtree(Subtag, NewSmartObject->BehaviorTree);
	}
}

void ATC_BaseInfectedController::ManageSight(AActor* Actor)
{
	BlackboardComponent->SetValue<UBlackboardKeyType_Object>("TargetActor", Actor);
	BlackboardComponent->ClearValue("HearingLocation");
}

void ATC_BaseInfectedController::ManageHearing(const FVector& HearingLocation)
{
	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>("HearingLocation", HearingLocation);
}

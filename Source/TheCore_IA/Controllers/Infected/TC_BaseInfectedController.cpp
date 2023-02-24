#include "Controllers/Infected/TC_BaseInfectedController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Characters/Infected/TC_BaseInfected.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

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
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->ConfigureSense(*HearingConfig);

	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
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

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ATC_BaseInfectedController::OnTargetPerceptionUpdated);
}

void ATC_BaseInfectedController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (IsValidStimulus<UAISense_Sight>(Stimulus))
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
		ManageSight(nullptr);
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

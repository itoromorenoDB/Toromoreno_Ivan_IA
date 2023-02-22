#include "Controllers/TC_MinionController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TheCore_IACharacter.h"

ATC_MinionController::ATC_MinionController() : Super()
{
	FSMComponent = CreateDefaultSubobject<UTC_FSMComponent>(TEXT("FSM Component"));
	ConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Config Sight"));
	ConfigDamage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	ConfigSight->SightRadius = 800.f;
	ConfigSight->LoseSightRadius = ConfigSight->SightRadius + 20.f;
	ConfigSight->PeripheralVisionAngleDegrees = 360.f;
	ConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	ConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	ConfigSight->DetectionByAffiliation.bDetectNeutrals = false;

	PerceptionComponent->ConfigureSense(*ConfigSight);
	PerceptionComponent->ConfigureSense(*ConfigDamage);
	PerceptionComponent->SetDominantSense(ConfigSight->GetSenseImplementation());
}

AActor* ATC_MinionController::GetTarget() const
{
	return CurrentTarget.IsValid() ? CurrentTarget.Get() : nullptr;
}

void ATC_MinionController::SetTarget(AActor* NewTarget)
{
	if (CurrentTarget.Get() == NewTarget)
		return;

	BlackboardComponent->SetValue<UBlackboardKeyType_Object>("TargetActor", NewTarget);
	CurrentTarget = NewTarget;
	TargetChanged.ExecuteIfBound(NewTarget);
}

void ATC_MinionController::InitFSM()
{
	//ChangeFSMState(EState::GoToTarget);
	MainTarget = CurrentTarget;
}

void ATC_MinionController::ChangeFSMState(EState State)
{
	if (FSMComponent)
	{
		//FSMComponent->ChangeState(State);
	}
}

FGenericTeamId ATC_MinionController::GetGenericTeamId() const
{
	ATC_MinionCharacter* Minion = Cast<ATC_MinionCharacter>(GetPawn());
	return Minion ? Minion->GetGenericTeamId() : FGenericTeamId();
}

void ATC_MinionController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATC_MinionCharacter* Minion = Cast<ATC_MinionCharacter>(InPawn);
	UBehaviorTree* BehaviorTree = Minion ? Minion->BehaviorTree : nullptr;

	if (BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*BehaviorTree);

		BlackboardComponent->SetValue<UBlackboardKeyType_Bool>("CanAttack", false);
	}
}

void ATC_MinionController::BeginPlay()
{
	Super::BeginPlay();
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ATC_MinionController::OnPerceptionUpdated);
}

void ATC_MinionController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus) == UAISense_Sight::StaticClass() || 
			UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus) == UAISense_Damage::StaticClass())
		{
			ReactToSight(Actor);
		}
	}
	else
	{
		if (!LostTargetTimer.IsValid())
		{
			GetWorldTimerManager().SetTimer(LostTargetTimer, this, &ATC_MinionController::OnLostTarget, 3.f);
		}
	}
}

void ATC_MinionController::ReactToSight(AActor* Target)
{
	if (Target->IsA<ATheCore_IACharacter>())
	{
		if (LostTargetTimer.IsValid())
		{
			GetWorldTimerManager().ClearTimer(LostTargetTimer);
		}

		SetTarget(Target);
	}
}

void ATC_MinionController::OnLostTarget()
{
	if (LostTargetTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(LostTargetTimer);
	}

	SetTarget(MainTarget.Get());
}

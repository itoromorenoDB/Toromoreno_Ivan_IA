#include "Controllers/TC_MinionController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "TheCore_IACharacter.h"

ATC_MinionController::ATC_MinionController() : Super()
{
	FSMComponent = CreateDefaultSubobject<UTC_FSMComponent>(TEXT("FSM Component"));
	ConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Config Sight"));
	ConfigDamage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));

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

	CurrentTarget = NewTarget;
	TargetChanged.ExecuteIfBound(NewTarget);
}

void ATC_MinionController::InitFSM()
{
	ChangeFSMState(EState::GoToTarget);
	MainTarget = CurrentTarget;
}

void ATC_MinionController::ChangeFSMState(EState State)
{
	if (FSMComponent)
	{
		FSMComponent->ChangeState(State);
	}
}

FGenericTeamId ATC_MinionController::GetGenericTeamId() const
{
	ATC_MinionCharacter* Minion = Cast<ATC_MinionCharacter>(GetPawn());
	return Minion ? Minion->GetGenericTeamId() : FGenericTeamId();
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

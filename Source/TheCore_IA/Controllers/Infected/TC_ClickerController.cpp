#include "Controllers/Infected/TC_ClickerController.h"
#include <Perception/AISense_Hearing.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Perception/AISenseConfig_Hearing.h>
#include <Perception/AIPerceptionComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>

ATC_ClickerController::ATC_ClickerController()
{
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;

	if (PerceptionComponent)
	{
		PerceptionComponent->SetDominantSense(HearingConfig->GetSenseImplementation());
	}
}

void ATC_ClickerController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACharacter* InfectedChar = Cast<ACharacter>(GetPawn());
	UCharacterMovementComponent* MovementComp = InfectedChar ? InfectedChar->GetCharacterMovement() : nullptr;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (MovementComp)
		{
			MovementComp->MaxWalkSpeed = 300.f;
		}

		if (IsValidStimulus<UAISense_Hearing>(Stimulus))
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

		BlackboardComponent->ClearValue("HearingLocation");
	}
}

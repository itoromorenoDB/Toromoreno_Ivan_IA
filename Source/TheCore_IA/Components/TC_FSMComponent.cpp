#include "Components/TC_FSMComponent.h"
#include "FSM/TC_State.h"
#include "GameFramework/Controller.h"

void UTC_FSMComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (const TPair<EState, TSoftClassPtr<UTC_State>> State : States)
	{
		UObject* StateToLoad = State.Value.ToSoftObjectPath().TryLoad();
		UClass* BaseClass = State.Value.Get();
		UTC_State* StateToChange = BaseClass ? BaseClass->GetDefaultObject<UTC_State>() : nullptr;
		if (StateToChange)
		{
			StateToChange->InitState(Cast<AController>(GetOwner()));
		}
	}
}

void UTC_FSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (UTC_State* State = CurrentState.IsValid() ? CurrentState.Get() : nullptr)
	{
		State->OnUpdateState(DeltaTime);
	}
}

void UTC_FSMComponent::ChangeState(EState NewState)
{
	if (!States.Contains(NewState))
		return;

	TSoftClassPtr<UTC_State> MapState = States[NewState];
	MapState.ToSoftObjectPath().TryLoad();
	UClass* BaseClass = MapState.Get();
	UTC_State* StateToChange = BaseClass ? BaseClass->GetDefaultObject<UTC_State>() : nullptr;
	UTC_State* State = CurrentState.IsValid() ? CurrentState.Get() : nullptr;

	if (State)
	{
		State->OnExitState();
	}

	if (StateToChange)
	{
		CurrentState = StateToChange;
		StateToChange->OnEnterState();
	}
}


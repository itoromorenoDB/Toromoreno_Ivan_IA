#include "Components/TC_FSMComponents.h"
#include "../FSM/TC_State.h"
#include "GameFramework/Controller.h"


void UTC_FSMComponents::BeginPlay()
{
	Super::BeginPlay();
	for (const TPair<EState, TSoftClassPtr<UTC_State>> State : States)
	{
		State.Value.ToSoftObjectPath().TryLoad();
		UClass* BaseClass = State.Value.Get();
		UTC_State* StateToChange = BaseClass ? BaseClass->GetDefaultObject<UTC_State>() : nullptr;
		if (StateToChange)
		{
			StateToChange->InitState(Cast<AController>(GetOwner()));
		}
	}
		
}


void UTC_FSMComponents::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (UTC_State* State = CurrentState.IsValid() ? CurrentState.Get() : nullptr)
	{
		State->OnUpdateState(DeltaTime);
	}
}

void UTC_FSMComponents::ChangeState(EState NewState)
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


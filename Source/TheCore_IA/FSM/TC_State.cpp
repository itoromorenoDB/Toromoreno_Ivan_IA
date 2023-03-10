#include "TC_State.h"

void UTC_State::InitState(AController* NewOwnerController)
{
	OwnerController = NewOwnerController;
}

AController* UTC_State::GetOwnerController() const
{
	return OwnerController.IsValid() ? OwnerController.Get() : nullptr;
}
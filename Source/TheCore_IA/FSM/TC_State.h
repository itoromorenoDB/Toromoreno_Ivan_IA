#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_State.generated.h"

class AController;

UCLASS()
class THECORE_IA_API UTC_State : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnEnterState() {};
	virtual void OnUpdateState(float DeltaTime) {};
	virtual void OnExitState() {};

	virtual void InitState(AController* NewOwnerController);

protected:
	AController* GetOwnerController() const;

	TWeakObjectPtr<AController> OwnerController = nullptr;
	
};

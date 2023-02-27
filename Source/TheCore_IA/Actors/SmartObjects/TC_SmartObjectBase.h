#pragma once

#include "CoreMinimal.h"
#include "TC_SmartObjectBase.generated.h"

class UBehaviorTree;
class UBillboardComponent;
class UArrowComponent;

UCLASS()
class THECORE_IA_API ATC_SmartObjectBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
		UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBillboardComponent* BillboardComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UArrowComponent* ArrowComponent = nullptr;

	ATC_SmartObjectBase();
};

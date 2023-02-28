#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_SmartObjectBasic.generated.h"

class USmartObjectComponent;

UCLASS()
class THECORE_IA_API ATC_SmartObjectBasic : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "AI")
		USmartObjectComponent* SmartObjectComponent = nullptr;
		
	ATC_SmartObjectBasic();

};

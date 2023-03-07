// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GenericTeamAgentInterface.h>
#include "TC_BaseInfected.generated.h"

class UBehaviorTree;
class USplineComponent;
class ATC_SmartObjectBase;

DECLARE_DELEGATE_OneParam(FSmartObjectChanged, ATC_SmartObjectBase*)

UCLASS()
class THECORE_IA_API ATC_BaseInfected : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, Category = AI)
		ATC_SmartObjectBase* CurrentSmartObject = nullptr;
	UPROPERTY()
		ATC_SmartObjectBase* MainSmartObject = nullptr;

	uint8 CurrentTeam;
	FSmartObjectChanged OnSmartObjectChanged;

	ATC_BaseInfected();

	void ResetSmartObject();
	void SetCurrentSmartObject(ATC_SmartObjectBase* NewSmartObject);

protected:
	void BeginPlay() override;
};

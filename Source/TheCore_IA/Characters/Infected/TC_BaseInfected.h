// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TC_BaseInfected.generated.h"

class UBehaviorTree;

UCLASS()
class THECORE_IA_API ATC_BaseInfected : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree = nullptr;
	ATC_BaseInfected();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:

	virtual void BeginPlay() override;
};

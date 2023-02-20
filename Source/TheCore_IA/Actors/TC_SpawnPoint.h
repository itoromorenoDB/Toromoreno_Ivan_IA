// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_SpawnPoint.generated.h"

class ATC_MinionCharacter;

UCLASS()
class THECORE_IA_API ATC_SpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATC_MinionCharacter> ClassToSpawn;
	UPROPERTY(EditAnywhere)
		AActor* Target = nullptr;

	ATC_SpawnPoint();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle SpawnTimer;

	void SpawnMinion();


};

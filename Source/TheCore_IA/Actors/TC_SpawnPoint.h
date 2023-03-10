#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/TC_MinionCharacter.h"
#include "TC_SpawnPoint.generated.h"

class ATC_MinionCharacter;

UCLASS()
class THECORE_IA_API ATC_SpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATC_MinionCharacter> ClassToSpawn;
	UPROPERTY(EditAnyWhere)
		AActor* Target = nullptr;
	UPROPERTY(EditAnyWhere)
		ETeam CurrentTeam = ETeam::None;

	ATC_SpawnPoint();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle SpawnTimer;

	void SpawnMinion();

};

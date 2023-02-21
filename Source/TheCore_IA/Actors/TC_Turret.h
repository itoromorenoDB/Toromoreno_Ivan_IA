#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TC_DamageableInterface.h"
#include "Characters/TC_MinionCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "TC_Turret.generated.h"

class UStaticMeshComponent;

UCLASS()
class THECORE_IA_API ATC_Turret : public AActor, public ITC_DamageableInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(EditAnywhere)
		ETeam CurrentTeam = ETeam::None;

	ATC_Turret();

	FGenericTeamId GetGenericTeamId() const override;
};

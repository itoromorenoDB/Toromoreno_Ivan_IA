#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TC_MinionCharacter.generated.h"

class USphereComponent;

UCLASS()
class THECORE_IA_API ATC_MinionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* SphereComponent = nullptr;

	ATC_MinionCharacter();

protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

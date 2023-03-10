#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "TC_MinionCharacter.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	TeamBlue,
	TeamRed,

	None
};

class USphereComponent;
class UAnimMontage;

UCLASS()
class THECORE_IA_API ATC_MinionCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* SphereComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* Punch = nullptr;

	ETeam CurrentTeam = ETeam::None;

	ATC_MinionCharacter();
	float PlayPunchAnimation();
	FGenericTeamId GetGenericTeamId() const override;

protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GenericTeamAgentInterface.h>
#include "TC_BaseInfected.generated.h"

class UBehaviorTree;
class USplineComponent;
class ATC_SmartObjectBase;
class USphereComponent;
class ATC_Projectile;

DECLARE_DELEGATE_OneParam(FSmartObjectChanged, ATC_SmartObjectBase*)

USTRUCT(BlueprintType)
struct FTC_ComboInformation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
		TArray<UAnimMontage*> Attacks;
};

UCLASS()
class THECORE_IA_API ATC_BaseInfected : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATC_Projectile> ProjectileToSpawn;
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, Category = AI)
		ATC_SmartObjectBase* CurrentSmartObject = nullptr;
	UPROPERTY()
		ATC_SmartObjectBase* MainSmartObject = nullptr;
	UPROPERTY(EditDefaultsOnly)
		FTC_ComboInformation ComboInformation;
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* SphereComponent = nullptr;

	uint8 CurrentTeam;
	FSmartObjectChanged OnSmartObjectChanged;

	ATC_BaseInfected();

	void ResetSmartObject();
	void SetCurrentSmartObject(ATC_SmartObjectBase* NewSmartObject);
	void Shoot();
protected:
	void BeginPlay() override;

private:

	UFUNCTION()
		void OnAttackAreaOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackAreaOverlappedEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetCanAttack(AActor* ActorToAttack, bool bCanAttack);
};

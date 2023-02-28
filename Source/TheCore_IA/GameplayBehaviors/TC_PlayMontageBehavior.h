#pragma once

#include "CoreMinimal.h"
#include "GameplayBehavior.h"
#include "TC_PlayMontageBehavior.generated.h"

class UAnimMontage;

UCLASS()
class THECORE_IA_API UTC_PlayMontageBehavior : public UGameplayBehavior
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "SmartObject")
		UAnimMontage* MontageToPlay = nullptr;

	virtual bool Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config = nullptr, AActor* SmartObjectOwner = nullptr) override;

private:

	UPROPERTY()
		AActor* CurrentAvatar = nullptr;

	FTimerHandle AnimTimer;
	void OnAnimTimer();
};

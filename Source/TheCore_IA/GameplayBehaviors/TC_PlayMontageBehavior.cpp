#include "GameplayBehaviors/TC_PlayMontageBehavior.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

bool UTC_PlayMontageBehavior::Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config /*= nullptr*/, AActor* SmartObjectOwner /*= nullptr*/)
{
	ACharacter* Character = Cast<ACharacter>(&Avatar);
	if (!Character)
		return false;

	CurrentAvatar = &Avatar;
	const float AnimTime = Character->PlayAnimMontage(MontageToPlay);
	Character->GetWorldTimerManager().SetTimer(AnimTimer, this, &UTC_PlayMontageBehavior::OnAnimTimer, AnimTime);
	return true;
}

void UTC_PlayMontageBehavior::OnAnimTimer()
{
	if (!CurrentAvatar)
		return;

	EndBehavior(*CurrentAvatar);
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheCore_IAGameMode.h"
#include "TheCore_IACharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheCore_IAGameMode::ATheCore_IAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

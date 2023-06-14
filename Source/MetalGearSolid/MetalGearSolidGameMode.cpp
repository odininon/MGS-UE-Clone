// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetalGearSolidGameMode.h"
#include "MetalGearSolidCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMetalGearSolidGameMode::AMetalGearSolidGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

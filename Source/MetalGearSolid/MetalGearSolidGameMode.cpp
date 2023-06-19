// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetalGearSolidGameMode.h"
#include "MetalGearSolidCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMetalGearSolidGameMode::AMetalGearSolidGameMode()
{
	// set default pawn class to our Blueprinted character
	if (static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter")); PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	if (static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/MetalGearSolid/BP_PlayerController")); PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

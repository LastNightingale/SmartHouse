// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmartHouseGameMode.h"
#include "SmartHouseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASmartHouseGameMode::ASmartHouseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

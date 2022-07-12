// Copyright Epic Games, Inc. All Rights Reserved.

#include "MagicBornGameMode.h"
#include "MagicBornHUD.h"
#include "MagicBornCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMagicBornGameMode::AMagicBornGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMagicBornHUD::StaticClass();
}

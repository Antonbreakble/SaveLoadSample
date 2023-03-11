// Copyright Epic Games, Inc. All Rights Reserved.

#include "SaveLoadSampleGameMode.h"
#include "SaveLoadSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASaveLoadSampleGameMode::ASaveLoadSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

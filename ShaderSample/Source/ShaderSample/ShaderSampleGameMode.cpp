// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderSampleGameMode.h"
#include "ShaderSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShaderSampleGameMode::AShaderSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

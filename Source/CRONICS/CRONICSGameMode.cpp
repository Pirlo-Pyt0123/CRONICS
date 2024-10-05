// Copyright Epic Games, Inc. All Rights Reserved.

#include "CRONICSGameMode.h"
#include "CRONICSPawn.h"

ACRONICSGameMode::ACRONICSGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ACRONICSPawn::StaticClass();
}


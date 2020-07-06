// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RTDGameMode.h"
#include "RTDPlayerController.h"
#include "RTDPawn.h"

ARTDGameMode::ARTDGameMode()
{
	// no pawn by default
	DefaultPawnClass = ARTDPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ARTDPlayerController::StaticClass();
}

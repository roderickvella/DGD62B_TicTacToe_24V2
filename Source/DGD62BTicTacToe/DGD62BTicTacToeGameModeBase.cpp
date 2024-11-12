// Copyright Epic Games, Inc. All Rights Reserved.


#include "DGD62BTicTacToeGameModeBase.h"
#include "MyPlayerController.h"

ADGD62BTicTacToeGameModeBase::ADGD62BTicTacToeGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

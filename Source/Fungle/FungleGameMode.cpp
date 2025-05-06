// Copyright Epic Games, Inc. All Rights Reserved.

#include "FungleGameMode.h"
#include "FunglePlayerController.h"
#include "FungleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFungleGameMode::AFungleGameMode()
{
	PlayerControllerClass = AFunglePlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
    if(PlayerControllerBPClass.Class != nullptr)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
}

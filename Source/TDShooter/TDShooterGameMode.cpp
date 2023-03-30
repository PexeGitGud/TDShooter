#include "TDShooterGameMode.h"
#include "TDShooterPlayerController.h"
#include "TDShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDShooterGameMode::ATDShooterGameMode()
{
	PlayerControllerClass = ATDShooterPlayerController::StaticClass();
}
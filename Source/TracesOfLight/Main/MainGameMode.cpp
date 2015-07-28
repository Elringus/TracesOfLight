#include "TracesOfLight.h"
#include "MainGameMode.h"
#include "MainCharacter.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> playerPawnBPClass(TEXT("/Game/Blueprints/Dirk"));

	if (playerPawnBPClass.Class != NULL)
		DefaultPawnClass = playerPawnBPClass.Class;
}

void AMainGameMode::StartPlay()
{
	Super::StartPlay();
	StartMatch();

}

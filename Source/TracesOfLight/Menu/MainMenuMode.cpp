#include "TracesOfLight.h"
#include "MainMenuMode.h"
#include "./GUI/MainMenuWidget.h"

AMainMenuMode::AMainMenuMode()
{
	DefaultPawnClass = nullptr;

}

void AMainMenuMode::StartPlay()
{
	Super::StartPlay();
	StartMatch();

	UMainMenuWidget::Create(GetWorld());
}

#include "TracesOfLight.h"
#include "MainMenuWidget.h"

UMainMenuWidget* UMainMenuWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UMainMenuWidget>(worldContextObject);
	if (!widget) return nullptr;

	widget->playButton = Cast<UButton>(widget->GetWidgetFromName(TEXT("PlayButton")));
	widget->quitButton = Cast<UButton>(widget->GetWidgetFromName(TEXT("QuitButton")));

	widget->playButton->OnClicked.AddDynamic(widget, &UMainMenuWidget::OnPlayButtonClicked);
	widget->quitButton->OnClicked.AddDynamic(widget, &UMainMenuWidget::OnQuitButtonClicked);

	GetPlayerController()->bShowMouseCursor = true;

	return widget;
}

void UMainMenuWidget::OnPlayButtonClicked()
{
	GetPlayerController()->bShowMouseCursor = false;
	LoadLevel(TEXT("Island"));
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

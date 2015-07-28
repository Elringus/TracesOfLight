#include "TracesOfLight.h"
#include "EndLevelWidget.h"

UEndLevelWidget* UEndLevelWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UEndLevelWidget>(worldContextObject);
	if (!widget) return nullptr;

	widget->replayButton = Cast<UButton>(widget->GetWidgetFromName(TEXT("ReplayButton")));
	widget->quitButton = Cast<UButton>(widget->GetWidgetFromName(TEXT("QuitButton")));

	widget->replayButton->OnClicked.AddDynamic(widget, &UEndLevelWidget::OnReplayButtonClicked);
	widget->quitButton->OnClicked.AddDynamic(widget, &UEndLevelWidget::OnQuitButtonClicked);

	GetPlayerController()->bShowMouseCursor = true;
	GetPlayerController()->SetPawn(nullptr);

	return widget;
}

void UEndLevelWidget::OnReplayButtonClicked()
{
	GetPlayerController()->bShowMouseCursor = false;
	LoadLevel(TEXT("Island"));
}

void UEndLevelWidget::OnQuitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

#pragma once

#include "BaseWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class TRACESOFLIGHT_API UMainMenuWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Main Menu",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "GUI")
		static UMainMenuWidget* Create(UObject* worldContextObject);

private:
	class UButton* playButton;
	class UButton* quitButton;

	UFUNCTION() void OnPlayButtonClicked();
	UFUNCTION() void OnQuitButtonClicked();
};
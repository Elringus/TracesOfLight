#pragma once

#include "BaseWidget.h"
#include "EndLevelWidget.generated.h"

UCLASS()
class TRACESOFLIGHT_API UEndLevelWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create End Level Menu",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "GUI")
		static UEndLevelWidget* Create(UObject* worldContextObject);

private:
	class UButton* replayButton;
	class UButton* quitButton;

	UFUNCTION() void OnReplayButtonClicked();
	UFUNCTION() void OnQuitButtonClicked();
};
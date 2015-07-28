#pragma once

#include "GameFramework/GameMode.h"
#include "MainMenuMode.generated.h"

UCLASS(MinimalAPI)
class AMainMenuMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMainMenuMode();

protected:
	virtual void StartPlay() override;
	
};

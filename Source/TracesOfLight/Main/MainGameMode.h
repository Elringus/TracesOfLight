#pragma once

#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

UCLASS(MinimalAPI)
class AMainGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMainGameMode();

protected:
	virtual void StartPlay() override;

};

#pragma once

#include "Engine.h"
#include "Main/MainCharacter.h"
#include "Main/PostProcessController.h"

#define Print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, text)

DECLARE_LOG_CATEGORY_EXTERN(TOL, Log, All);

FORCEINLINE void LoadLevel(FString levelName)
{
	if (!GEngine)
	{
		UE_LOG(TOL, Error, TEXT("LoadLevel failed: GEngine is not available."));
		return;
	}

	GEngine->GameViewport->RemoveAllViewportWidgets();

	UWorld* world = nullptr;

	for (TObjectIterator<AActor> obj; obj; ++obj)
		if (obj->IsActorInitialized()) { world = obj->GetWorld(); break; }

	if (world) UGameplayStatics::OpenLevel(world, FName(*levelName));
	else UE_LOG(TOL, Error, TEXT("LoadLevel failed: can't find active UWorld pointer."));
}

FORCEINLINE AMainCharacter* GetMainCharacter()
{
	for (TObjectIterator<AMainCharacter> mc; mc; ++mc)
		if (mc->IsActorInitialized()) return *mc;

	return nullptr;
}

FORCEINLINE APlayerController* GetPlayerController(UObject* worldContextObject = nullptr)
{
	if (worldContextObject)
		return UGameplayStatics::GetPlayerController(worldContextObject, 0);

	// Works only for single-world cases. Not usable for multiplayer projects.
	for (TObjectIterator<APlayerController> pc; pc; ++pc)
		if (pc->IsActorInitialized()) return *pc;

	return nullptr;
}

FORCEINLINE APostProcessController* GetCameraEffects()
{
	for (TObjectIterator<APostProcessController> mc; mc; ++mc)
		if (mc->IsActorInitialized()) return *mc;

	return nullptr;
}

#include "TracesOfLight.h"
#include "BaseWidget.h"

TArray<UClass*> UBaseWidget::widgetClassesCache;

void UBaseWidget::DestroyAllWidgets(UObject* worldContextObject)
{
	worldContextObject->GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
	widgetClassesCache.Empty();
}

void UBaseWidget::CacheWidgetClasses()
{
	// It seems GC cleans the cache while in build.
	// So disabling it and waiting for Epic to fix the static UMG refs bug.
	//if (widgetClassesCache.Num() > 0) return;
	widgetClassesCache.Empty();

	TArray<FString> widgetPaths;
	widgetPaths.Add(TEXT("/Game/UMG/MainMenu/MainMenu.MainMenu_C"));
	widgetPaths.Add(TEXT("/Game/UMG/EndLevel/EndLevel.EndLevel_C"));


	for (int i = 0; i < widgetPaths.Num(); i++)
	{
		auto widgetClass = LoadObject<UClass>(NULL, *widgetPaths[i]);
		if (widgetClass) widgetClassesCache.AddUnique(widgetClass);
	}
}
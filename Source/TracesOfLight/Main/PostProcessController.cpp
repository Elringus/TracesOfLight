#include "TracesOfLight.h"
#include "PostProcessController.h"

APostProcessController::APostProcessController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APostProcessController::BeginPlay()
{
	Super::BeginPlay();
	
	for (TObjectIterator<APostProcessVolume> volIt; volIt; ++volIt)
		if (volIt->IsActorInitialized()) PostProcessVolume = *volIt;

	if (!PostProcessVolume)
	{
		UE_LOG(TOL, Warning, TEXT("PostProcessController wasn't able to find PostProcessVolume"));
		return;
	}

	PostProcessVolume->bUnbound = true;

	PostProcessVolume->Settings.bOverride_LPVIntensity = true;
	PostProcessVolume->Settings.LPVIntensity = LPVIntentisty;
	PostProcessVolume->Settings.bOverride_LPVSize = true;
	PostProcessVolume->Settings.LPVSize = LPVSize;
	PostProcessVolume->Settings.bOverride_LPVSecondaryOcclusionIntensity = true;
	PostProcessVolume->Settings.LPVSecondaryOcclusionIntensity = LPVSecondaryOcclusionIntensity;
	PostProcessVolume->Settings.bOverride_LPVSecondaryBounceIntensity = true;
	PostProcessVolume->Settings.LPVSecondaryBounceIntensity = LPVSecondaryBounceIntensity;

	PostProcessVolume->Settings.bOverride_AutoExposureMinBrightness = true;
	PostProcessVolume->Settings.AutoExposureMinBrightness = AutoExposureMinBrightness;

	PostProcessVolume->Settings.bOverride_DepthOfFieldMethod = true;
	PostProcessVolume->Settings.DepthOfFieldMethod = DepthOfFieldMethod;
	PostProcessVolume->Settings.bOverride_DepthOfFieldNearTransitionRegion = true;
	PostProcessVolume->Settings.DepthOfFieldNearTransitionRegion = DepthOfFieldNearTransitionRegion;
	PostProcessVolume->Settings.bOverride_DepthOfFieldFarTransitionRegion = true;
	PostProcessVolume->Settings.DepthOfFieldFarTransitionRegion = DepthOfFieldFarTransitionRegion;
	PostProcessVolume->Settings.bOverride_DepthOfFieldNearBlurSize = true;
	PostProcessVolume->Settings.DepthOfFieldNearBlurSize = DepthOfFieldNearBlurSize;
	PostProcessVolume->Settings.bOverride_DepthOfFieldFarBlurSize = true;
	PostProcessVolume->Settings.DepthOfFieldFarBlurSize = DepthOfFieldFarBlurSize;
}

void APostProcessController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void APostProcessController::SwitchMenuBlur(bool isBlurOn)
{
	if (!PostProcessVolume) return;

	PostProcessVolume->Settings.DepthOfFieldNearTransitionRegion = isBlurOn ? 0 : DepthOfFieldNearTransitionRegion;
	PostProcessVolume->Settings.DepthOfFieldFarTransitionRegion = isBlurOn ? 0 : DepthOfFieldFarTransitionRegion;
	PostProcessVolume->Settings.DepthOfFieldNearBlurSize = isBlurOn ? 100 : DepthOfFieldNearBlurSize;
	PostProcessVolume->Settings.DepthOfFieldFarBlurSize = isBlurOn ? 100 : DepthOfFieldFarBlurSize;
}


#pragma once

#include "GameFramework/Actor.h"
#include "PostProcessController.generated.h"

UCLASS()
class TRACESOFLIGHT_API APostProcessController : public AActor
{
	GENERATED_BODY()
	
public:	
	APostProcessController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float LPVIntentisty = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float LPVSize = 20000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float LPVSecondaryOcclusionIntensity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float LPVSecondaryBounceIntensity = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float AutoExposureMinBrightness = .5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	TEnumAsByte<EDepthOfFieldMethod> DepthOfFieldMethod = EDepthOfFieldMethod::DOFM_Gaussian;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float DepthOfFieldNearTransitionRegion = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float DepthOfFieldFarTransitionRegion = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float DepthOfFieldNearBlurSize = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Effects")
	float DepthOfFieldFarBlurSize = 1.f;

protected:
	class APostProcessVolume* PostProcessVolume;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
};

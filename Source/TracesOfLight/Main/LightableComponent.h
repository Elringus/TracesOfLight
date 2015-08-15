#pragma once

#include "Components/ActorComponent.h"
#include "LightableComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRACESOFLIGHT_API ULightableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULightableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float MinEmission = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float MaxEmission = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float ActivationTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matinee")
	class AMatineeActor* Matinee;

	virtual void BeginPlay() override;
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

	void ActivateLight();

protected:
	bool IsLightActivated = false;
	TArray<UMaterialInstanceDynamic*> EmissionMaterials;

};

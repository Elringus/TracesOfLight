#include "TracesOfLight.h"
#include "LightableComponent.h"
#include "Matinee/MatineeActor.h"

ULightableComponent::ULightableComponent()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

void ULightableComponent::BeginPlay()
{
	Super::BeginPlay();

	auto owner = GetOwner();
	if (!owner) return;

	TArray<UStaticMeshComponent*> comps;
	owner->GetComponents(comps);
	if (comps.Num() == 0) return;

	auto mesh = comps[0];
	if (!mesh) return;

	for (int i = 0; i < mesh->GetMaterials().Num(); i++)
	{
		if (!mesh->GetMaterial(i)) continue;

		float emissionPower;
		mesh->GetMaterial(i)->GetScalarParameterValue(TEXT("EmissionPower"), emissionPower);
		if (emissionPower > 0) 
		{
			auto matInst = mesh->CreateAndSetMaterialInstanceDynamic(i);
			matInst->SetScalarParameterValue(TEXT("EmissionPower"), MinEmission);
			EmissionMaterials.Add(matInst);
		}
	}
}

void ULightableComponent::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction );

	if (IsLightActivated)
	{
		for (auto mat : EmissionMaterials)
		{
			float curEmission;
			mat->GetScalarParameterValue(TEXT("EmissionPower"), curEmission);
			mat->SetScalarParameterValue(TEXT("EmissionPower"), 
				FMath::Lerp(curEmission, MaxEmission, deltaTime * ActivationTime));
		}
	}
}

void ULightableComponent::ActivateLight()
{
	IsLightActivated = true;

	if (Matinee) Matinee->Play();
}

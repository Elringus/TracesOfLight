#pragma once

#include "GameFramework/Actor.h"
#include "Crystal.generated.h"

UCLASS()
class TRACESOFLIGHT_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	ACrystal();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class USphereComponent* TriggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	class UParticleSystem* ExplosionParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glow")
	float GlowAmplitude = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glow")
	float SleepGlow = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glow")
	float FloatGlow = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Glow")
	float GravityGlow = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float")
	float FloatRadius = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float")
	float FloatSpeed = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float")
	float FloatHeight = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float")
	float FloatAmlitude = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float")
	float FloatRotationSpeed = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	float GravityRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	float GravityForce = 1500.f;

	UFUNCTION()
	void Consume();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

private:
	class ACharacter* mainCharacter;
	class UMaterialInstanceDynamic* crystalMaterial;
	FVector sleepPoint; // where this actor will rest on ground
	
	FVector GetSleepPoint() const;
};

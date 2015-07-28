#pragma once

#include "GameFramework/Actor.h"
#include "SoundTrigger.generated.h"

UCLASS()
class TRACESOFLIGHT_API ASoundTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoundTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class USphereComponent* TriggerSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base")
	class UAudioComponent* Sound;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	
};

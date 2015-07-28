#pragma once

#include "GameFramework/Actor.h"
#include "EndLevelTrigger.generated.h"

UCLASS()
class TRACESOFLIGHT_API AEndLevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AEndLevelTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class USphereComponent* TriggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnTriggerEvents")
	class AMatineeActor* ShipMatinee;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
};

#pragma once

#include "GameFramework/Actor.h"
#include "JumpOffTrigger.generated.h"

UCLASS()
class TRACESOFLIGHT_API AJumpOffTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AJumpOffTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class USphereComponent* TriggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnTriggerEvents")
	class AMatineeActor* JumpOffMatinee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnTriggerEvents")
	class AMatineeActor* LowerGangwayMatinee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnTriggerEvents")
	class ABlockingVolume* GangwayBlock;

	void Play(class AMainCharacter* character);

protected:
	class AMainCharacter* AttachedCharacter;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

};

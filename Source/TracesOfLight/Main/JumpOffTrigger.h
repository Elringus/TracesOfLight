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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Matinee")
	class AMatineeActor* Matinee;

	void Play(class AMainCharacter* character);

protected:
	class AMainCharacter* AttachedCharacter;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

};

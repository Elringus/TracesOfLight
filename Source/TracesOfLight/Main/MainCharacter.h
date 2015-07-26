#pragma once

#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS(Config=Game)
class AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	class UParticleSystem* LightPath;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
};


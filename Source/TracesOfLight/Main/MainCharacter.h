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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	void MoveForward(float value);
	void MoveRight(float value);

	/** 
	 *  Called via input to turn at a given rate. 
	 *  @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float rate);

	/**
	 *  Called via input to turn look up/down at a given rate. 
	 *  @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

};


#include "TracesOfLight.h"
#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(.0f, 540.f, .0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = .2f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 300.f;	
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; 

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	check(inputComponent);
	inputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	inputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	inputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	inputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	inputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	inputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	inputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	inputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);
}

void AMainCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != .0f))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(.0f, rotation.Yaw, .0f);

		const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != .0f))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(.0f, rotation.Yaw, .0f);
	
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

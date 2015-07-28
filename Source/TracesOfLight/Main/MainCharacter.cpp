#include "TracesOfLight.h"
#include "MainCharacter.h"
#include "Crystal.h"

AMainCharacter::AMainCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(85.f, 50.f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);

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
}

#pragma region INPUT
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	check(inputComponent);
	inputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	inputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	inputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	inputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

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
#pragma endregion

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void AMainCharacter::OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, 
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	auto crystal = Cast<ACrystal>(otherActor);
	if (crystal) 
	{
		crystal->Consume();
		ActivateLightPath();
	}
}

void AMainCharacter::ActivateLightPath()
{
	if (!LightPath || LightPathActivated) return;

	LightPathActivated = true;
	LightPathComponent = UGameplayStatics::SpawnEmitterAttached(LightPath, GetRootComponent(), TEXT("LightPath"), FVector(0, 0, LightPathHeight));
}

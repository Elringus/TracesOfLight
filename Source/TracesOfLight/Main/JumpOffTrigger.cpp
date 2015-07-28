#include "TracesOfLight.h"
#include "JumpOffTrigger.h"
#include "Matinee/MatineeActor.h"
#include "MainCharacter.h"

AJumpOffTrigger::AJumpOffTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	if (TriggerSphere)
	{
		TriggerSphere->SetSphereRadius(50.f);
		TriggerSphere->bGenerateOverlapEvents = true;
		TriggerSphere->SetCollisionProfileName(TEXT("OverlapAll"));
		RootComponent = TriggerSphere;

		TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AJumpOffTrigger::OnOverlapBegin);
	}

	HornSound = CreateDefaultSubobject<UAudioComponent>("HornSound");
	if (HornSound)
	{
		HornSound->bStopWhenOwnerDestroyed = false;
		HornSound->bAutoActivate = false;
		HornSound->AttachTo(RootComponent);
	}
}

void AJumpOffTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJumpOffTrigger::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (JumpOffMatinee && JumpOffMatinee->bIsPlaying && AttachedCharacter)
		AttachedCharacter->SetFlying(GetActorLocation());
	else if (AttachedCharacter)
	{
		AttachedCharacter->SetFlying(FVector::ZeroVector);
		AttachedCharacter = nullptr;
	}
}

void AJumpOffTrigger::Play(AMainCharacter* character)
{
	if (!character) return;

	if (character->LightPathComponent)
		character->LightPathComponent->DestroyComponent();

	if (JumpOffMatinee)
	{
		AttachedCharacter = character;
		JumpOffMatinee->Play();
	}

	if (LowerGangwayMatinee)
		LowerGangwayMatinee->Play();

	if (GangwayBlock)
		GangwayBlock->Destroy();

	if (HornSound)
	{
		FTimerHandle hornTimerHandle;
		GetWorldTimerManager().SetTimer(hornTimerHandle, this, &AJumpOffTrigger::PlayHornSound, HornSoundStartDelay, false);
	}
}

void AJumpOffTrigger::OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, 
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	Play(Cast<AMainCharacter>(otherActor));
}

void AJumpOffTrigger::PlayHornSound()
{
	if (HornSound) HornSound->Play();
}

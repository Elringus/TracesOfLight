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
	}
}

void AJumpOffTrigger::Play(AMainCharacter* character)
{
	if (Matinee)
	{
		AttachedCharacter = character;
		Matinee->Play();
	}
}

void AJumpOffTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJumpOffTrigger::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (Matinee->bIsPlaying && AttachedCharacter)
	{
		AttachedCharacter->SetActorLocation(GetActorLocation());
		AttachedCharacter->SetActorRotation(GetActorRotation());
		AttachedCharacter->IsMatineeFlying = true;
	}
	else if (AttachedCharacter)
	{
		AttachedCharacter->IsMatineeFlying = false;
		AttachedCharacter = nullptr;
	}
}


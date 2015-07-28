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
}

void AJumpOffTrigger::OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, 
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	Play(Cast<AMainCharacter>(otherActor));
}


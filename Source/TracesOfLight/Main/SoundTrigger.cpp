#include "TracesOfLight.h"
#include "SoundTrigger.h"
#include "MainCharacter.h"

ASoundTrigger::ASoundTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	if (TriggerSphere)
	{
		TriggerSphere->SetSphereRadius(300.f);
		TriggerSphere->bGenerateOverlapEvents = true;
		TriggerSphere->SetCollisionProfileName(TEXT("OverlapAll"));
		RootComponent = TriggerSphere;

		TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ASoundTrigger::OnOverlapBegin);
	}

	Sound = CreateDefaultSubobject<UAudioComponent>("Sound");
	if (Sound)
	{
		Sound->bStopWhenOwnerDestroyed = false;
		Sound->bAutoActivate = false;
		Sound->AttachTo(RootComponent);
	}
}

void ASoundTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoundTrigger::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void ASoundTrigger::OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, 
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (Cast<AMainCharacter>(otherActor))
	{
		if (Sound) Sound->Play();
		Destroy();
	}
}

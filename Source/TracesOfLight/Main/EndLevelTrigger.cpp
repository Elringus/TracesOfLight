#include "TracesOfLight.h"
#include "EndLevelTrigger.h"
#include "Matinee/MatineeActor.h"
#include "MainCharacter.h"

AEndLevelTrigger::AEndLevelTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	if (TriggerSphere)
	{
		TriggerSphere->SetSphereRadius(300.f);
		TriggerSphere->bGenerateOverlapEvents = true;
		TriggerSphere->SetCollisionProfileName(TEXT("OverlapAll"));
		RootComponent = TriggerSphere;

		TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AEndLevelTrigger::OnOverlapBegin);
	}
}

void AEndLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndLevelTrigger::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void AEndLevelTrigger::OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, 
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (Cast<AMainCharacter>(otherActor)) 
		ShipMatinee->Play();
}



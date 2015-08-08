#include "TracesOfLight.h"
#include "Crystal.h"
#include "LightableComponent.h"

ACrystal::ACrystal()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	if (BaseMesh)
	{
		BaseMesh->bCastDynamicShadow = false;
		BaseMesh->bAffectDynamicIndirectLighting = true;
		BaseMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
		BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		BaseMesh->bShouldUpdatePhysicsVolume = true;
		BaseMesh->bCanEverAffectNavigation = false;
		BaseMesh->SetSimulatePhysics(true);
		RootComponent = BaseMesh;
	}

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	if (TriggerSphere)
	{
		TriggerSphere->SetSphereRadius(50.f);
		TriggerSphere->bGenerateOverlapEvents = true;
		TriggerSphere->SetCollisionProfileName(TEXT("OverlapAll"));
		TriggerSphere->AttachTo(RootComponent);
	}

	ConsumeSound = CreateDefaultSubobject<UAudioComponent>("ConsumeSound");
	if (ConsumeSound)
	{
		ConsumeSound->bStopWhenOwnerDestroyed = false;
		ConsumeSound->bAutoActivate = false;
		ConsumeSound->AttachTo(RootComponent);
	}
}

void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	
	mainCharacter = GetMainCharacter();
	crystalMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	initialPoint = GetActorLocation();
}

void ACrystal::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (mainCharacter)
	{
		auto distance = FVector::Dist(mainCharacter->GetActorLocation(), GetActorLocation());
		float curGlow; 
		crystalMaterial->GetScalarParameterValue("EmissionPower", curGlow);

		if (IsCharacterInLOS() && distance < GravityRadius)
		{
			if (!BaseMesh->IsSimulatingPhysics())
				BaseMesh->SetSimulatePhysics(true);
			sleepPoint = FVector::ZeroVector;

			auto forceVector = (mainCharacter->GetActorLocation() - GetActorLocation());
			forceVector.Normalize();
			BaseMesh->AddForce(forceVector * GravityForce, NAME_None, true);

			crystalMaterial->SetScalarParameterValue("EmissionPower", 
				FMath::Lerp(curGlow, GravityGlow, deltaTime));
		}
		else if (IsCharacterInLOS() && distance < FloatRadius)
		{
			if (BaseMesh->IsSimulatingPhysics())
				BaseMesh->SetSimulatePhysics(false);

			if (sleepPoint.IsZero())
				sleepPoint = GetSleepPoint();

			SetActorLocation(FMath::Lerp(GetActorLocation(), 
				sleepPoint + FVector(0, 0, FloatHeight + FMath::Sin(GetWorld()->TimeSeconds) * FloatAmlitude), deltaTime * FloatSpeed));
			AddActorWorldRotation(FRotator(-10, 5, 7) * FloatRotationSpeed * deltaTime);

			crystalMaterial->SetScalarParameterValue("EmissionPower",
				FMath::Lerp(curGlow, FloatGlow + FMath::Sin(GetWorld()->TimeSeconds) * GlowAmplitude, deltaTime));
		}
		else
		{
			if (BaseMesh->IsSimulatingPhysics())
				BaseMesh->SetSimulatePhysics(false);

			if (sleepPoint.IsZero()) 
				sleepPoint = GetSleepPoint();
			SetActorLocation(FMath::Lerp(GetActorLocation(), sleepPoint, deltaTime));

			crystalMaterial->SetScalarParameterValue("EmissionPower",
				FMath::Lerp(curGlow, SleepGlow, deltaTime));
		}
	}
}

void ACrystal::Consume()
{
	if (ExplosionParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticles, GetActorLocation());

	for (TObjectIterator<ULightableComponent> l; l; ++l)
	{
		if (FVector::Dist(GetActorLocation(), l->GetOwner()->GetActorLocation()) < LightActivationRange)
			l->ActivateLight();
	}

	if (ConsumeSound) ConsumeSound->Play();

	Destroy();
}

FVector ACrystal::GetSleepPoint() const
{
	if (!IsSleepingOnGround) return initialPoint;

	FHitResult hit(ForceInit);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingle(hit, GetActorLocation(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 1000), ECC_WorldStatic, params))
		return hit.ImpactPoint;
	else return FVector::ZeroVector;
}

bool ACrystal::IsCharacterInLOS() const
{
	return mainCharacter && mainCharacter->GetController()->LineOfSightTo(this);
}

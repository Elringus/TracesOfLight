#include "TracesOfLight.h"
#include "Crystal.h"

ACrystal::ACrystal()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	if (BaseMesh)
	{
		BaseMesh->bCastDynamicShadow = false;
		BaseMesh->bAffectDynamicIndirectLighting = true;
		static FName MeshCollision(TEXT("PhysicsActor"));
		BaseMesh->SetCollisionProfileName(MeshCollision);
		BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		BaseMesh->bShouldUpdatePhysicsVolume = true;
		BaseMesh->bCanEverAffectNavigation = false;
		BaseMesh->SetSimulatePhysics(true);
		BaseMesh->SetNotifyRigidBodyCollision(true);
		BaseMesh->OnComponentHit.AddDynamic(this, &ACrystal::OnHit);
		RootComponent = BaseMesh;
	}
}

void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	
	mainCharacter = GetMainCharacter();
}

void ACrystal::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (mainCharacter)
	{
		auto distance = FVector::Dist(mainCharacter->GetActorLocation(), GetActorLocation());

		if (distance < GravityRadius)
		{
			if (!BaseMesh->IsSimulatingPhysics())
				BaseMesh->SetSimulatePhysics(true);
			sleepPoint = FVector::ZeroVector;

			auto forceVector = (mainCharacter->GetActorLocation() - GetActorLocation());
			forceVector.Normalize();
			BaseMesh->AddForce(forceVector * GravityForce, NAME_None, true);
		}
		else if (distance < FloatRadius)
		{
			if (BaseMesh->IsSimulatingPhysics())
				BaseMesh->SetSimulatePhysics(false);

			if (sleepPoint.IsZero())
				sleepPoint = GetSleepPoint();

			SetActorLocation(FMath::Lerp(GetActorLocation(), 
				sleepPoint + FVector(0, 0, FloatHeight + FMath::Sin(GetWorld()->TimeSeconds) * FloatAmlitude), deltaTime * FloatSpeed));
			AddActorWorldRotation(FRotator(-10, 5, 7) * FloatRotationSpeed * deltaTime);
		}
		else
		{
			if (BaseMesh->IsSimulatingPhysics())
				BaseMesh->SetSimulatePhysics(false);

			if (sleepPoint.IsZero()) 
				sleepPoint = GetSleepPoint();

			SetActorLocation(FMath::Lerp(GetActorLocation(), sleepPoint, deltaTime));
		}
	}
}

void ACrystal::OnHit(AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	if (Cast<ACharacter>(otherActor))
		this->Destroy();
}

FVector ACrystal::GetSleepPoint()
{
	FHitResult hit(ForceInit);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingle(hit, GetActorLocation(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 1000), ECC_WorldStatic, params))
		return hit.ImpactPoint;
	else return FVector::ZeroVector;
}

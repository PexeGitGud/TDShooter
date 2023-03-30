#include "TDShooterBullet.h"
#include "TDShooterHealthBarComponent.h"

ATDShooterBullet::ATDShooterBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &ATDShooterBullet::Overlap);
}

void ATDShooterBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	lifetime -= DeltaTime;

	if (lifetime <= 0.f)
		Destroy();
}

void ATDShooterBullet::Overlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UTDShooterHealthBarComponent* healthBarComponent = (UTDShooterHealthBarComponent*)OtherActor->GetComponentByClass(UTDShooterHealthBarComponent::StaticClass());
	if (!healthBarComponent)
		return;
	
	healthBarComponent->TakeDamage(attack);

	Ricochet(OtherActor);

	ricochets--;

	if (ricochets <= 0)
	{
		Destroy();
	}
}

void ATDShooterBullet::AddImpulse(FVector direction, float speed)
{
	if (speed == 0.f)
		speed = bulletSpeed;

	((UStaticMeshComponent*)GetRootComponent())->AddImpulse(direction * speed);
}
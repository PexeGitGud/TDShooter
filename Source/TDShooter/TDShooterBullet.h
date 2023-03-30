#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDShooterBullet.generated.h"

UCLASS()
class ATDShooterBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDShooterBullet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float bulletSpeed = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float lifetime = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attack = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ricochets = 3;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Overlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void Ricochet(AActor* DamagedActor);

	UFUNCTION(BlueprintCallable)
	void AddImpulse(FVector direction, float speed = 0.f);
};
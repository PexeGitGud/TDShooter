#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TDShooterBullet.h"
#include "TDShooterPlayerController.generated.h"

UCLASS()
class ATDShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDShooterPlayerController();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATDShooterBullet> BulletToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float bulletFireRate = 0.2f;
	float currentBulletFireRate = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float bulletSpawnRadius = 75.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* ShootBulletSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;

protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay();

	void TryToShootBullet();

	void ShootBullet(FVector direction);

	void Move(const FInputActionValue& Value);
};
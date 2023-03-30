#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDShooterHealthBarComponent.h"
#include "TDShooterCharacter.generated.h"

UCLASS(Blueprintable)
class ATDShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATDShooterCharacter();

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<UTDShooterHealthBarComponent> HealthComponent;
};
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TDShooterHealthBarComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComponentReceiveDamageSignature);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComponentDieSignature);

UCLASS(Blueprintable, editinlinenew, meta = (BlueprintSpawnableComponent))
class UTDShooterHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attack = 10.f;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TakeDamage(float damage);

	UPROPERTY(BlueprintAssignable)
	FComponentReceiveDamageSignature OnTakeDamage;
	UPROPERTY(BlueprintAssignable)
	FComponentDieSignature OnDie;

protected:
	UPROPERTY(BlueprintReadOnly)
	float currentHealth;

	virtual void BeginPlay();

	UFUNCTION()
	void Die();
};
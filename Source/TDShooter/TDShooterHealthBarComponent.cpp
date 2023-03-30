#include "TDShooterHealthBarComponent.h"

void UTDShooterHealthBarComponent::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = maxHealth;
}

void UTDShooterHealthBarComponent::TakeDamage_Implementation(float damage)
{
	OnTakeDamage.Broadcast();

	currentHealth -= damage;

	if (currentHealth <= 0.f)
	{
		currentHealth = 0.f;

		Die();
	}
}

void UTDShooterHealthBarComponent::Die()
{
	OnDie.Broadcast();
}
#include "TDShooterPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TDShooterCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TDShooterHealthBarComponent.h"

ATDShooterPlayerController::ATDShooterPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATDShooterPlayerController::BeginPlay()
{ 
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATDShooterPlayerController::Tick(float DeltaTime)
{
	if (currentBulletFireRate > 0.f)
	{
		currentBulletFireRate -= DeltaTime;
	}
}

void ATDShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATDShooterPlayerController::TryToShootBullet);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDShooterPlayerController::Move);
	}
}

void ATDShooterPlayerController::TryToShootBullet()
{
	if (currentBulletFireRate <= 0.f)
	{
		currentBulletFireRate = bulletFireRate;

		FPlane mouseInputPlane = FPlane(0.f, 0.f, 1.f, GetPawn()->GetActorLocation().Z);

		FVector location, direction, intersection;
		DeprojectMousePositionToWorld(location, direction);
		intersection = FMath::RayPlaneIntersection(location, direction, mouseInputPlane);

		ShootBullet(intersection);
	}
}

void ATDShooterPlayerController::ShootBullet(FVector direction)
{
	if (!(UTDShooterHealthBarComponent*)GetPawn()->GetComponentByClass(UTDShooterHealthBarComponent::StaticClass()))
	{
		UE_LOG(LogClass, Error, TEXT("%s is missing a TDShooterHealthBarComponent!"), *GetDebugName(this))
		return;
	}

	FVector playerLocation = GetPawn()->GetActorLocation();
	FVector directionNormal = (direction - playerLocation).GetSafeNormal();
	const FVector location = directionNormal * bulletSpawnRadius + playerLocation;
	ATDShooterBullet* bullet = (ATDShooterBullet*)GetWorld()->SpawnActor(BulletToSpawn, &location, &FRotator::ZeroRotator);
	bullet->attack = ((UTDShooterHealthBarComponent*)GetPawn()->GetComponentByClass(UTDShooterHealthBarComponent::StaticClass()))->attack;
	bullet->AddImpulse(directionNormal);

	if(ShootBulletSound)
		ClientPlaySound(ShootBulletSound);
}

void ATDShooterPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}
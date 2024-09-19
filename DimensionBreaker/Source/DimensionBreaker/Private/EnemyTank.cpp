// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "PaperSpriteComponent.h"
#include "Projectile.h"
#include "PaperFlipbookComponent.h" 


AEnemyTank::AEnemyTank()
{
	PrimaryActorTick.bCanEverTick = true;


	
}

void AEnemyTank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (bIsReloaded && Canon)
	{
		//UE_LOG(LogTemp, Warning, TEXT("FIRE"))
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, Canon->GetSocketLocation("Projectile"), Canon->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}

}

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();

	GetSprite()->SetFlipbook(MovingAnimation);
}

void AEnemyTank::Tick(float time)
{

	Super::Tick(time);

	Rotate();
	//	Fire();
	
	bool bIsTurning = (FPlatformTime::Seconds() - LastTurnTime) > MovingTimeInSeconds;

	if (bIsTurning)
	{
		LastTurnTime = FPlatformTime::Seconds();
		Direction *= -1;
	}

	AddMovementInput(FVector(Direction, 0, 0), MovingSpeed);
	

	

}

void AEnemyTank::SetupCanon(UPaperSpriteComponent *canon)
{
	Canon = canon;
}

void AEnemyTank::Rotate()
{
	FRotator Rotation;
	if (bIsRotatingRight)
	{
		Rotation = Canon->GetRelativeRotation() - FRotator(1.f, 0.f, 0.f);
	}
	else
	{
		Rotation = Canon->GetRelativeRotation() + FRotator(1.f, 0.f, 0.f);
	}

	Rotation.Pitch = FMath::Clamp(Rotation.Pitch, -90.0f, 0.f);
	Canon->SetRelativeRotation(Rotation);

	if (FMath::IsNearlyEqual(Canon->GetRelativeRotation().Pitch, -90, 0.1))
	{
		bIsRotatingRight = false;
	}
	else
		if (FMath::IsNearlyEqual(Canon->GetRelativeRotation().Pitch, 0, 0.1))
		{
			bIsRotatingRight = true;
		}
}

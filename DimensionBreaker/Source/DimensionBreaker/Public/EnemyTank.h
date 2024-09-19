// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyTank.generated.h"


class UPaperSpriteComponent;
class AProjectile;



class UPaperFlipbook;

/**
 * 
 */
UCLASS()
class DIMENSIONBREAKER_API AEnemyTank : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyTank();

	void Fire();

	void BeginPlay() override;

	void Tick(float time) override;


	UFUNCTION(BlueprintCallable)
	void SetupCanon(UPaperSpriteComponent *Canon);



private:

	void Rotate();

	float LastFireTime = 0;
	float ReloadTimeInSeconds = 3;
	float LaunchSpeed = 1000;
	bool bIsRotatingRight = true;

	float MovingSpeed = 0.1f;
	float MovingTimeInSeconds = 5;
	float LastTurnTime = 0;
	int Direction = 1;


	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> Projectile_BP;
	
	
	UPaperSpriteComponent* Canon;


	UPROPERTY(EditDefaultsOnly, Category = Animantion)
	UPaperFlipbook* MovingAnimation;;
};

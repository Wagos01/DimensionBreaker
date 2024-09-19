// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerCharacter2D.generated.h"


class UPaperFlipbook;
class UInventory;

UCLASS()
class DIMENSIONBREAKER_API APlayerCharacter2D : public APaperCharacter
{
	GENERATED_BODY()


public:
	APlayerCharacter2D();


	void UpdateAnimation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(EditAnywhere, Category = "Animations");
	UPaperFlipbook* FlipIdle;

	UPROPERTY(EditAnywhere, Category = "Animations");
	UPaperFlipbook* FlipWalk;


	UPROPERTY(EditAnywhere, Category = "Movement");
	float Speed = 300.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup");
	UInventory* Inventory = nullptr;


	FVector Scale;//A sprite scale-je

	void SwitchDimension();

	//Movement es animacio
	void MoveUp(float Value);
	void MoveRight(float Value);


	bool switched = false;




	bool bIsFalling = false;
	float CurrentFallingSpeed = 0;
	float InitialFallingSpeed = 10;
	float GravityAcceleration = 1000;
};

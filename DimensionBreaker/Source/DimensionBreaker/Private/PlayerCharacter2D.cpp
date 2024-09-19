// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "PaperFlipbookComponent.h"  
#include "Inventory.h"
#include "PlayerCharacter2D.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter2D::APlayerCharacter2D()
{
	PrimaryActorTick.bCanEverTick = true;


	
	Inventory = CreateDefaultSubobject<UInventory>("Inventory");
	
	
	
	

}

void APlayerCharacter2D::UpdateAnimation()
{
	FVector Velocity = GetVelocity();
	double VectorSize = Velocity.Size();

	UPaperFlipbook* DesiredAnimation = FlipIdle;


	if (VectorSize > 0.0f)
	{
		DesiredAnimation = FlipWalk;
	}
	

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);	
	}

}

void APlayerCharacter2D::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);


	//GetCharacterMovement()->MaxFlySpeed = 1;
	Scale = GetSprite()->GetRelativeScale3D();
}

void APlayerCharacter2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	

	if (bIsFalling)
	{
		// Fokozatosan növeljük az esési sebességet a Z tengelyen
		CurrentFallingSpeed += GravityAcceleration * DeltaTime;

		FVector NewLocation = GetActorLocation();
		NewLocation.Z -= CurrentFallingSpeed * DeltaTime;

		SetActorLocation(NewLocation);

		// Ellenőrizzük, hogy a karakter elérte-e a talajt
		FVector Start = GetActorLocation();
		FVector End = Start - FVector(0.0f, 0.0f, 100.0f); // Rövid vonal lefelé

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility,
			CollisionParams
		);

		if (bHit && HitResult.Distance <= CurrentFallingSpeed * DeltaTime)
		{
			// Állítsuk le az esést és helyezzük a karaktert a talajra
			bIsFalling = false;
			FVector GroundedLocation = GetActorLocation();
			GroundedLocation.Z = HitResult.Location.Z;
			SetActorLocation(GroundedLocation);
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			GetCharacterMovement()->GravityScale = 100.0f;
		}
	}
	//else
	//{
	//	// Ellenőrizzük, hogy a karakter még mindig a talajon van-e
	//	if (!GetCharacterMovement()->IsMovingOnGround())
	//	{
	//		// Ha a karakter nincs a talajon, állítsuk be az esési állapotot
	//		bIsFalling = true;
	//		CurrentFallingSpeed = 0.0f; // Esés sebességének visszaállítása kezdeti értékre
	//	}
	//}
	
	
	
	
	
	
	
	
	UpdateAnimation();

	
}


void APlayerCharacter2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveRight",this, &APlayerCharacter2D::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &APlayerCharacter2D::MoveUp);


	PlayerInputComponent->BindAction("SwitchDimension", IE_Pressed, this, &APlayerCharacter2D::SwitchDimension);
	//PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &APlayerCharacter2D::MoveDown);
}

void APlayerCharacter2D::SwitchDimension()
{
	AMainGameMode::SetDimension(!AMainGameMode::GetDimension());

	if (AMainGameMode::GetDimension()) // 3D
	{

		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		GetCharacterMovement()->GravityScale = 0.0f;
	}
	else // 2D
	{
		bIsFalling = true;
		CurrentFallingSpeed = InitialFallingSpeed;
	}
}

//Z
void APlayerCharacter2D::MoveUp(float Value)
{
	//AddMovementInput(FVector(0, 0, 1), Value);
	
	GetCharacterMovement()->Velocity.Z = Value * Speed;
}


//X 
void APlayerCharacter2D::MoveRight(float Value)
{
	GetCharacterMovement()->Velocity.X = Value * Speed;

	if (Value > 0.0f)
	{
		GetSprite()->SetRelativeScale3D(Scale);
	}
	else if (Value < 0.0f)
	{
		GetSprite()->SetRelativeScale3D(Scale * FVector(-1, 1, 1));
	}
}

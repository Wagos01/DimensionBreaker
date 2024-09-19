// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableObject.h"
#include "Blueprint/UserWidget.h"
#include "PaperFlipbookComponent.h" 
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCharacter2D.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include "ItemPopUpWidget.h"
#include "Components/TextBlock.h"


APickableObject::APickableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper Flipbook Component"));
	RootComponent = FlipbookComponent;



	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Collision"));
	PickupCollision->InitSphereRadius(50.0f); // Adjust radius as needed
	PickupCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // Use overlap profile

	PickupCollision->SetupAttachment(RootComponent);


	

}
void APickableObject::BeginPlay()
{
	Super::BeginPlay();


	// Bind overlap event
	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &APickableObject::OnOverlapBegin);
	PickupCollision->OnComponentEndOverlap.AddDynamic(this, &APickableObject::OnOverlapEnded);


	//Create the subtitle widget
	if (PickupTextWidgetClass)
	{
		ItemWidget = CreateWidget<UItemPopUpWidget>(GetWorld(), PickupTextWidgetClass);

		if (ItemWidget)
		{
			ItemWidget->AddToViewport();
			ItemWidget->SetVisibility(ESlateVisibility::Hidden); // Alapértelmezésben rejtve legyen
		}

	}

}

void APickableObject::Tick(float Delta)
{
	Super::Tick(Delta);

	//TODO atgondol es befejez
	if (bIsEquiped)
	{
		FlipbookComponent->SetFlipbook(Attacking);
	}
	else
	{
		FlipbookComponent->SetFlipbook(Idle);
	}

	//TODO ha lathatatlan akkor nem kell
	UpdateWidgetPosition(ItemWidget);
	ItemWidget->SetText();
}

void APickableObject::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<APlayerCharacter2D>(OtherActor);

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nem karakter"));
	}

	if (Player && OtherActor && OtherActor != this)
	{
		// Here you can enable pickup logic or allow the player to pick it up
		EnablePickup();
	}
}
void APickableObject::OnOverlapEnded(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Player = Cast<APlayerCharacter2D>(OtherActor);

	if (Player && OtherActor && OtherActor != this)
	{
		DisablePickup();
	}
}

void APickableObject::EnablePickup()
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);
}

void APickableObject::DisablePickup()
{
	ItemWidget->SetVisibility(ESlateVisibility::Collapsed);
}

//TODO Kitalal hogy lesz
void APickableObject::DropItem()
{
//	GetWorld()->SpawnActor<>();
}
void APickableObject::PickItem()
{

}

void APickableObject::UpdateWidgetPosition(UUserWidget* Widget)
{
	if (!Widget)
	{
		return;
	}

	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{

		//FVector WorldLocation = FlipbookComponent->GetSocketLocation("TextPosition");
		FVector WorldLocation = GetActorLocation() + FVector(-10,0,40); //TODO remove magic number


		FVector2D ScreenLocation;
		bool bProjected = UGameplayStatics::ProjectWorldToScreen(PlayerController, WorldLocation, ScreenLocation);

		if (bProjected)
		{
			// Convert the 3D world position to 2D screen position
			// Example of positioning the widget at the screen location
			//UWidgetLayoutLibrary::SlotAsCanvasSlot(Widget->GetRootWidget())->SetPosition(ScreenLocation);
		
			Widget->SetPositionInViewport(ScreenLocation);
		}
	}
	


}




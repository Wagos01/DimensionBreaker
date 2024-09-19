// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PickableObject.generated.h"


class UPaperFlipbook;
class USphereComponent;
class UUserWidget;
class UTextBlock;
class UItemPopUpWidget;

/**
 * 
 */
UCLASS(Abstract)
class DIMENSIONBREAKER_API APickableObject : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	APickableObject();
	
	virtual void Attack() PURE_VIRTUAL(AbstractClassBase::Attack, );

	//Spawns the item to the ground
	void DropItem();

	void PickItem();

	void BeginPlay() override;

	void Tick(float Delta) override;

	

protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickupCollision = nullptr;


	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookComponent = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UPaperFlipbook* Idle = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UPaperFlipbook* Attacking = nullptr;

	//TODO nem biztos kell
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<APickableObject> Class = nullptr;
	

	//UI
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UItemPopUpWidget> PickupTextWidgetClass = nullptr;


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnded(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void EnablePickup();
	void DisablePickup();

	//A foldon van vagy felvan veve
	bool bIsEquiped = false;

	//UPROPERTY(EditAnywhere, meta = (BindWidget))
	//UTextBlock* PickupText;

private:
	bool bIsPickupEnabled = false;

	void UpdateWidgetPosition(UUserWidget* Widget);

	UItemPopUpWidget* ItemWidget;

};

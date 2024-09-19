// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


class APickableObject;


UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	MeeleWeapon UMETA(DisplayName = "Meele Weapon"),
	RangedWeapon UMETA(DisplayName = "Ranged Weapon")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIMENSIONBREAKER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UInventory();

	TMap<EWeaponSlot, APickableObject*> WeaponInventory;

	//TODO Megoldani hogy a megfelelo Itemet droppolja es vegye fel 
	
	void AddItem(APickableObject*);

	void DropItem(EWeaponSlot);



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
		
};

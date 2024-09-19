// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DIMENSIONBREAKER_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainGameMode();
	void Tick(float Value) override;

	static void SetDimension(bool);
	static bool GetDimension();


private:
	static bool Dimension;

	
};

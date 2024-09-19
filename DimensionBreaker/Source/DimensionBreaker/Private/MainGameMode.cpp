// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

bool AMainGameMode::Dimension = true;

AMainGameMode::AMainGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainGameMode::Tick(float Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("%c"), (Dimension ? 't' : 'f'))
}

void AMainGameMode::SetDimension(bool d)
{
	Dimension = d;
}

bool AMainGameMode::GetDimension()
{
	return Dimension;
}

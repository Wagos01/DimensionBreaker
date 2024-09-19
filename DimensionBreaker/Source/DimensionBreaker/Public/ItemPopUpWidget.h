// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPopUpWidget.generated.h"


class UTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class DIMENSIONBREAKER_API UItemPopUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetText();

protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* TextBlock;

};

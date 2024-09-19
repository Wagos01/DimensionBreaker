// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPopUpWidget.h"
#include "Components/TextBlock.h"
#include <GameFramework/InputSettings.h>


void UItemPopUpWidget::SetText()
{
	FString text = "Press ";

	const UInputSettings* InputSettings = UInputSettings::GetInputSettings();

	const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

	auto NewText = FString("Error");

	for (const FInputActionKeyMapping& ActionMapping : ActionMappings)
	{
		if (ActionMapping.ActionName == "PickUp")
		{
			NewText = FString("Press " + ActionMapping.Key.GetDisplayName().ToString());
			break;
		}
	}
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*NewText)

	if (TextBlock)
	{
		TextBlock->SetText(FText::FromString(NewText));
		//TextBlock->SetText(FText::FromString("NewText"));
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CSaveFileSelectUI.h"
#include "CSaveGame.h"
#include "IPlayerUIController.h"

void UCSaveFileSelectUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SelectButton->OnReleased.RemoveDynamic(this, &Super::OnButtonClicked);
	SelectButton->OnReleased.AddDynamic(this, &UCSaveFileSelectUI::OnButtonClicked);
}

void UCSaveFileSelectUI::OnButtonClicked()
{
	//SaveFile->SaveSlotName;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());

	if (UIController == nullptr) return;
	UIController->SaveGame(SaveFile->SaveIndex);

	UIController->AddAlert(FText::FromString("Saved"));
}

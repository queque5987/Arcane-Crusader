// Fill out your copyright notice in the Description page of Project Settings.


#include "CESCUI.h"
#include "IPlayerUIController.h"
#include "CGameInstance.h"
#include "CSaveGame.h"

void UCESCUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BTNGameStart->OnReleased.RemoveDynamic(this, &Super::OnGameStartClicked);
	BTNGameStart->OnReleased.AddDynamic(this, &UCESCUI::OnGameResumeClicked);
	BTNQuit->OnReleased.RemoveDynamic(this, &Super::OnQuitClicked);
	BTNQuit->OnReleased.AddDynamic(this, &UCESCUI::OnToMainClicked);
	BTNSave->OnReleased.AddDynamic(this, &UCESCUI::OnSaveClicked);
	SlotSelectPanel->SetVisibility(ESlateVisibility::Hidden);
	BTNSelectClose->OnReleased.AddDynamic(this, &UCESCUI::OnSelectCloseClicked);
}

void UCESCUI::OnGameResumeClicked()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	UIController->SwitchESCMenu();
}

void UCESCUI::OnToMainClicked()
{
	FSoftObjectPath path = FSoftObjectPath("/Game/Resources/Levels/MainUILevel.MainUILevel");
	TSoftObjectPtr<UWorld> MenuLevel(path);
	//if (AMainUIGameMode* GM = Cast<AMainUIGameMode>(GetWorld()->GetAuthGameMode()))
	//{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MenuLevel);
	UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());
	GI->SelectedSaveSlot = -1;
	//	if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
	//	{
	//		e->MainUI->SetVisibility(ESlateVisibility::Hidden);
	//	}
	//}
}

void UCESCUI::OnSaveClicked()
{
	SlotSelectPanel->SetVisibility(ESlateVisibility::Visible);

	SelectSlotList->ClearListItems();

	for (int i = 0; i < 3; i++)
	{
		UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Save" + FString::FromInt(i), i));
		if (SaveGameInstance == nullptr)
		{
			SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
			SaveGameInstance->SaveIndex = i;
		}
		SelectSlotList->AddItem(SaveGameInstance);
	}
}

void UCESCUI::OnSelectCloseClicked()
{
	SlotSelectPanel->SetVisibility(ESlateVisibility::Hidden);
}

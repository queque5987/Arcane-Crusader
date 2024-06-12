// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainUI.h"
#include "IItemManager.h"
#include "MainUIGameMode.h"
#include "CSaveGame.h"

void UCMainUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BTNGameStart->OnReleased.AddDynamic(this, &UCMainUI::OnGameStartClicked);
	BTNLoadGame->OnReleased.AddDynamic(this, &UCMainUI::OnLoadGameClicked);
	BTNQuit->OnReleased.AddDynamic(this, &UCMainUI::OnQuitClicked);
	BTNClose->OnReleased.AddDynamic(this, &UCMainUI::OnCloseClicked);

	SavePanel->SetVisibility(ESlateVisibility::Hidden);
}

void UCMainUI::OnGameStartClicked()
{
	if (AMainUIGameMode* GM = Cast<AMainUIGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//FString LevelName = L"/Game/Resources/Levels/Startlevel";
		//UGameplayStatics::OpenLevel(GetOwningPlayer(), *LevelName, true);

		OnLoadingScreenSet.Broadcast(FName(TEXT("Startlevel")));

		//UGameplayStatics::OpenLevelBySoftObjectPtr(GetOwningPlayer()->GetWorld(), GM->LevelToLoad);
		if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
		{
			e->MainUI->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}

void UCMainUI::OnLoadGameClicked()
{
	SavePanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	MainPanel->SetVisibility(ESlateVisibility::Hidden);
	LoadSaveSlot();
}

void UCMainUI::OnCloseClicked()
{
	SavePanel->SetVisibility(ESlateVisibility::Hidden);
	MainPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UCMainUI::OnQuitClicked()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UCMainUI::LoadSaveSlot()
{
	SaveSlotList->ClearListItems();

	for (int i = 0; i < 3; i++)
	{
		UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Save" + FString::FromInt(i), i));
		//if (SaveGameInstance == nullptr) continue;
		SaveSlotList->AddItem(SaveGameInstance);
	}
}

//ACPlayerController* UCMainUI::GetPlayerController()
//{
//	if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
//	{
//		return e;
//	}
//	return nullptr;
//}

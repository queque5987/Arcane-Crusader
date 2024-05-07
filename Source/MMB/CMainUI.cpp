// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainUI.h"
#include "MainUIGameMode.h"

void UCMainUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BTNGameStart->OnClicked.AddDynamic(this, &UCMainUI::OnGameStartClicked);
	BTNLoadGame->OnClicked.AddDynamic(this, &UCMainUI::OnLoadGameClicked);
	BTNQuit->OnClicked.AddDynamic(this, &UCMainUI::OnQuitClicked);
}

void UCMainUI::OnGameStartClicked()
{
	if (AMainUIGameMode* GM = Cast<AMainUIGameMode>(GetWorld()->GetAuthGameMode()))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, GM->LevelToLoad);
		if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
		{
			e->MainUI->SetVisibility(ESlateVisibility::Hidden);
		}
		//SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UCMainUI::OnLoadGameClicked()
{
}

void UCMainUI::OnQuitClicked()
{
}

//ACPlayerController* UCMainUI::GetPlayerController()
//{
//	if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
//	{
//		return e;
//	}
//	return nullptr;
//}

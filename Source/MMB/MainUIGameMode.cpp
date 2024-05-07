// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIGameMode.h"
#include "CMainUIPawn.h"

AMainUIGameMode::AMainUIGameMode()
{
	DefaultPawnClass = ACMainUIPawn::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();

	FSoftObjectPath path = FSoftObjectPath("/Game/TestLevel1.TestLevel1");
	TSoftObjectPtr<UWorld> testlevel(path);
	LevelToLoad = testlevel;
}

//void AMainUIGameMode::BeginPlay()
//{
//	/*MainUI = Cast<UCMainUI>(CreateWidget<UUserWidget>(this, UCMainUI::StaticClass()));
//	if (IsValid(MainUI))
//	{
//		MainUI->AddToViewport();
//		MainUI->SetVisibility(ESlateVisibility::Hidden);
//	}*/
//
//}
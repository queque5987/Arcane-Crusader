// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/CanvasPanel.h"
#include "PCH.h"
#include "CMainUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingScreenSet_Main, FName, LoadingMapName);

UCLASS()
class MMB_API UCMainUI : public UUserWidget, public IIWidgetInteract
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintAssignable, Category = "LoadingScreen")
	FOnLoadingScreenSet_Main OnLoadingScreenSet;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> MainPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNGameStart;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNLoadGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNQuit;



	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SavePanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> SaveSlotList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNLoad;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNClose;

	UFUNCTION(BlueprintCallable)
	void OnGameStartClicked();

	UFUNCTION(BlueprintCallable)
	void OnLoadGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnCloseClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuitClicked();
protected:
	virtual void NativeOnInitialized() override;


	void LoadSaveSlot();
	
};

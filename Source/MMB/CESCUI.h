// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMainUI.h"
#include "CESCUI.generated.h"

UCLASS()
class MMB_API UCESCUI : public UCMainUI
{
	GENERATED_BODY()
	
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNSave;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UCanvasPanel> MainPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SlotSelectPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> SelectSlotList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNSelectClose;

	UFUNCTION()
	void OnGameResumeClicked();

	UFUNCTION()
	void OnToMainClicked();

	UFUNCTION()
	void OnSaveClicked();

	UFUNCTION()
	void OnSelectCloseClicked();
};

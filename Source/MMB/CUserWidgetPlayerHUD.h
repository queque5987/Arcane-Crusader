// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Listview.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "CUserWidgetPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCUserWidgetPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCUserWidgetPlayerHUD(const FObjectInitializer& ObjectInitializer);
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> EnemyHPBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> QuestList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> DieUI;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DieBG;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DieText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DieSubText;

	void InitializeUI();
	void ShowDieUI(bool b);
	void Tick_DieUIAnim(float DeltaTime);
	bool GetContinueRevive() { return bContinueRevive; }

private:
	bool bContinueRevive;
};

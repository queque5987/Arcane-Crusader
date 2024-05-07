// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PCH.h"
#include "CMainUI.generated.h"

UCLASS()
class MMB_API UCMainUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNGameStart;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNLoadGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BTNQuit;

	UFUNCTION(BlueprintCallable)
	void OnGameStartClicked();

	UFUNCTION(BlueprintCallable)
	void OnLoadGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuitClicked();

//protected:
//	ACPlayerController* GetPlayerController();
	
};

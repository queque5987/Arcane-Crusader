// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TileView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "IWidgetInteract.h"
#include "CSaveFileUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingScreenSet_Load, FName, LoadingMapName);

UCLASS()
class MMB_API UCSaveFileUI : public UUserWidget, public IUserObjectListEntry, public IIWidgetInteract
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SelectButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SaveSlotName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerGold;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Weapon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Artifact;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Armor;

	class UCSaveGame* SaveFile;

public:

	UPROPERTY(BlueprintAssignable, Category = "LoadingScreen")
	FOnLoadingScreenSet_Load OnLoadingScreenSet;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnInitialized() override;
	UFUNCTION()
	virtual void OnButtonClicked();
	//virtual void OnRightClicked();
	//virtual void SwitchPressed(bool Pressed);
	//virtual bool GetbPressed();
};

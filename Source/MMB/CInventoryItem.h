// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "IWidgetInteract.h"
#include "CInventoryItem.generated.h"

UCLASS()
class MMB_API UCInventoryItem : public UUserWidget, public IUserObjectListEntry, public IIWidgetInteract
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	virtual void NativeOnInitialized() override;
	UObject* ItemData;
	double ClickedSec;
	bool IsInShop;
	bool bPicked = false;
	int32 Rarity = 0;
	int ItemType;

	void Equip();
	void UnEquip(FString EquippedSpace);
public:
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();
	UFUNCTION()
	virtual void OnHovered();
	UFUNCTION()
	virtual void OnUnHovered();
	UFUNCTION()
	void OnButtonReleased();
	UFUNCTION()
	void OnButtonPressed();
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;
	
	FTimerHandle UnHoverTimerHandler;

	virtual void OnRightClicked() override;

	UFUNCTION()
	void ReleasePutItem();
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantity;

	void SwitchbPicked(bool bForce = false, bool e = false);
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

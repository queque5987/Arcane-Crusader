// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "CInventoryItem.h"
#include "CInventory.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCInventory : public UUserWidget
{
	GENERATED_BODY()

	UCInventory(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> ItemList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerGold;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Weapon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Artifact;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Armor;

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	bool EquipItem(int ItemType, class UCInventoryItemData& ToEquipItemData);
};

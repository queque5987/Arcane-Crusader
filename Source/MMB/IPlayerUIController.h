// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerUIController.generated.h"

UINTERFACE(MinimalAPI)
class UIPlayerUIController : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIPlayerUIController
{
	GENERATED_BODY()

public:
	//virtual void SetSelectedPortal(UWorld* Level, FVector Location) {};
	virtual void SetSelectedPortal(int ArrIndex) {};
	virtual bool SetInventoryVisibility() { return false; };
	virtual void AddInventoryItem(UClass* ItemClass) {};
	virtual void AddInventoryItem(class UCInventoryItemData* ItemData) {};
	virtual void RemoveInventoryItem(class UCInventoryItemData* ItemData) {};
	virtual bool IsOnShop() { return false; };
//DEPRECATED
	virtual TArray<UObject*> GetInventoryItems() { return TArray<UObject*>(); };
	virtual void SetShopInventoryItems(TObjectPtr<class UTileView>& ShopTileList) {};
	virtual void ResumeShopInventoryItems() {};
	virtual void AddAlert(FText e) {};

	virtual void SetPressedButton(UUserWidget* SelectedButton) {};
	//virtual void SetPressedQuest(UUserWidget* SelectedQuest) {};
};

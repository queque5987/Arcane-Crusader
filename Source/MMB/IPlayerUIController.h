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
	virtual void SetSelectedPortal(int ArrIndex) {};
	virtual bool SetInventoryVisibility() { return false; };
	virtual void AddInventoryItem(UClass* ItemClass) {};
	virtual void AddInventoryItem(class UCInventoryItemData* ItemData) {};
	virtual void ShowItemDetailUI(class UCInventoryItemData* ItemData) {};
	virtual void UnShowItemDetailUI() {};
	virtual void RemoveInventoryItem(class UCInventoryItemData* ItemData) {};
	virtual bool RemoveEquippedItem(FString EquippedSpace, class UCInventoryItemData* ItemData) { return false; };
	virtual bool IsOnShop() { return false; };

	virtual void SwitchESCMenu() {};

	virtual bool EquipItem(int ItemType, class UCInventoryItemData& ItemData) { return false; };

//DEPRECATED
	//virtual TArray<UObject*> GetInventoryItems() { return TArray<UObject*>(); };

	virtual void SetShopInventoryItems(TObjectPtr<class UTileView>& ShopTileList) {};
	virtual void ResumeShopInventoryItems() {};
	virtual void AddAlert(FText e) {};

	virtual void SetPressedButton(UUserWidget* SelectedButton) {};

	virtual void RemoveQuest(UObject* QuestDat){}
	virtual void MoveQuestToClearedByQuestName(FString QuestName) {}
	virtual UINT32 IsPossesQuestCleared(FString QuestName) { return 0; }
	virtual bool IsQualifiedQuest(TArray<FString> RequiredQuestsArr) { return false; }

	virtual void SaveGame(int32 SlotIndex) {};
	virtual void LoadGame(int32 SaveSlot) {};

};

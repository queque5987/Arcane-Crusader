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
	virtual void SetHPPercent(float NewPercent) {};
	virtual void SetMaxHP(float NewMaxHP) {};
	virtual void SetStaminaPercent(float NewPercent) {};
	virtual void SetMaxStamina(float NewMaxStamina) {};
	virtual void SetCenterProgress(float NewPercent) {};
	virtual void AddRecentDamage(float Damage) {};
	virtual void SetEnemyHP(float NewPercent) {};
	virtual void SetEnemyHPVisibility(bool e) {};

	virtual void SetSelectedPortal(int ArrIndex) {};
	virtual bool SetInventoryVisibility() { return false; };
	virtual void AddInventoryItem(UClass* ItemClass) {};
	virtual void AddInventoryItem(class UCInventoryItemData* ItemData, bool OnPickup = false) {};
	virtual int32 UseItem(int32 QuickSlotNum) { return 0; };
	virtual void ShowItemDetailUI(class UCInventoryItemData* ItemData) {};
	virtual void UnShowItemDetailUI() {};
	virtual void RemoveInventoryItem(class UCInventoryItemData* ItemData) {};
	virtual bool RemoveEquippedItem(FString EquippedSpace, class UCInventoryItemData* ItemData) { return false; };
	virtual bool IsOnShop() { return false; };

	virtual void AddQuest(struct FQuestsRow* Q) {};
	virtual void RemoveQuest(struct FQuestsRow* Q) {};
	virtual void RemoveQuestByName(FString QuestName) {};

	virtual void SwitchESCMenu() {};

	virtual bool EquipItem(int ItemType, class UCInventoryItemData& ItemData) { return false; };

	virtual void SetShopInventoryItems(TObjectPtr<class UTileView>& ShopTileList) {};
	virtual void ResumeShopInventoryItems() {};
	virtual void AddAlert(FText e) {};

	virtual void SetPressedButton(UUserWidget* SelectedButton) {};

	virtual void ManualQuestClear(FString QuestName, int AchieveQuestRequirementIndex) {}
	virtual void RemoveQuest(UObject* QuestDat){}
	virtual void MoveQuestToClearedByQuestName(FString QuestName) {}
	virtual UINT32 IsPossesQuestCleared(FString QuestName) { return 0; }
	virtual bool IsQualifiedQuest(TArray<FString> RequiredQuestsArr) { return false; }
	virtual void HoxyPossessClearableQuest(class ACStaticNPC* NPC, TArray<class UCQuestData*>& OutArr) {};

	virtual void EquippedItemStat(struct ItemStat& SumItemStat) {};
	virtual bool IsSocketEmpty(int ItemType) { return false; }

	virtual void SaveGame(int32 SlotIndex) {};
	virtual void SaveGame(TArray<uint8>& MemoryAddress) {};
	virtual void LoadGame(int32 SaveSlot) {};
	virtual void LoadGame(TArray<uint8> MemoryAddress) {};

	virtual void DragInItem(class UCInventoryItemData* ToDragItem) {};
	virtual void DragItem(FVector2D WidgetTranslation) {};
	virtual void DragItem() {};
	virtual void DragOutItem() {};
	//virtual class UCInventoryItemData* SetUpQuickSlot() { return nullptr; }; Changed Name
	virtual class UCInventoryItemData* GetQuickSlot() { return nullptr; };

// Battle Staff UI
	virtual void SetBattleVIsibility(bool e) {};
	virtual void SetBruteMode(bool e) {};
	virtual void SetBruteGauge(float Percent) {};
	virtual void SetBruteCooldown(float Percent) {};
	virtual void SetBruteCooldownParam(float MaxCooldown) {};

// Rifle Staff UI
	virtual void SetAimVisibility(bool e) {};
	virtual void SetAimSpriteColorOverlay(float Index) {};
	virtual bool GetWeaponChangeReady() { return false; }
	virtual void SetAimSpriteBlur(float NewBlur) {};
	virtual void SetAimProgressBarPercent(float NewPercent) {};
	virtual void SetRifleSelectCylinder(FVector Bullets, FVector WeaponDisplaySequence) {};
	virtual void DoRifleSelectBarrelRoll() {};
};

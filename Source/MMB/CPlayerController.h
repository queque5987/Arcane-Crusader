// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCH.h"
#include "CInventory.h"
#include "CInventoryItemData.h"
#include "CMainUI.h"
#include "CAlert.h"
#include "CUserWidgetPlayerHUD.h"
#include "CDamageUI.h"
#include "Containers/Queue.h"
#include "CNPCConversation.h"
#include "CWidgetDroppedItemList.h"
#include "CButtonAction.h"
#include "CDroppedItem.h"
#include "IPlayerUIController.h"
#include "CPlayerController.generated.h"

UCLASS()
class MMB_API ACPlayerController : public APlayerController, public IIPlayerUIController
{
	GENERATED_BODY()
	ACPlayerController();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ItemInventoryAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> NPCConversationAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> MainUIAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> AlertAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UCDamageUI> DamageAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> DroppedItemListAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UCButtonAction> ButtonActionAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ItemDetailAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UCESCUI> ESCMenuAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UCInventoryItem> DraggingItemAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCUserWidgetPlayerHUD* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCInventory* ItemInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCNPCConversation* NPCConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCMainUI* MainUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCAlert* AlertUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCWidgetDroppedItemList* DroppedItemList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCItemDetailUI* ItemDetailUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCESCUI* ESCUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UCInventoryItem* DraggingItem;
	class UCInventoryItemData* DraggingItemDat;

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	TArray<class UCAlert*> AlertUIList;
	FTimerHandle DamageShowTimer;
	TQueue<class UCDamageUI*> DamageUIQueue;

	TArray<class ACDroppedItem*> DroppedItemPtrArr;

	//TArray<class UCQuest*> ClearedQuestArr;
	TArray<FString> ClearedQuestArr;

	class UCButtonAction* ButtonActionUI;
	class ACClimbableRope* GraspingRope;
	int32 JumpStartPoint;
	UFUNCTION()
	void DequeueDamageUI();

	void StartBattleMap();
	struct ItemStat* CurrentItemStat;
public:
	virtual void SetHPPercent(float NewPercent) override;
	virtual void SetMaxHP(float NewMaxHP) override;
	virtual void SetStaminaPercent(float NewPercent) override;
	virtual void SetMaxStamina(float NewMaxStamina) override;
	virtual void SetCenterProgress(float NewPercent) override;
	virtual void AddRecentDamage(float Damage) override;
	virtual void SetEnemyHPVisibility(bool e) override;
	virtual void SetEnemyHP(float NewPercent) override;

	virtual bool SetInventoryVisibility() override;
	virtual void AddInventoryItem(UClass* ItemClass) override;
	virtual void AddInventoryItem(class UCInventoryItemData* ItemData, bool OnPickup = false) override;
	virtual int32 UseItem(int32 QuickSlotNum) override;
	virtual void RemoveInventoryItem(class UCInventoryItemData* ItemData) override;
	virtual bool RemoveEquippedItem(FString EquippedSpace, class UCInventoryItemData* ItemData) override;
	virtual void ShowItemDetailUI(class UCInventoryItemData* ItemData) override;
	virtual void UnShowItemDetailUI() override;
	virtual bool IsOnShop() override;
	virtual void SetShopInventoryItems(TObjectPtr<class UTileView>& ShopTileList) override;
	virtual void ResumeShopInventoryItems() override;

	virtual void SwitchESCMenu() override;

	virtual bool EquipItem(int ItemType, class UCInventoryItemData& ItemData) override;

	virtual void SetPressedButton(UUserWidget* SelectedButton) override;

	void SetNPCConversationVisibility(bool e, class ACStaticNPC* npc = nullptr);
	void ResetNPCConversation(class ACStaticNPC* npc);
	virtual void AddAlert(FText e) override;
	void ShowDamageUI(float Damage, FVector Location, FColor C = FColor::White, bool IsAttacked = false);
	void AlertSwingby(float e, FText Line);
	virtual void AddQuest(struct FQuestsRow* Q) override;
	virtual void RemoveQuest(struct FQuestsRow* Q) override;
	virtual void RemoveQuestByName(FString QuestName) override;
	//void AddQuest(UFMonsterConfigure* MonsterConfig);
	//Deprecated
	void AddQuest(class UCQuestData* QuestData);
	//void CheckQuest(UObject* ToCheckObject);
	void CheckQuest(UObject* ToCheckObject, int AchievedActionType = 0);
	//void CheckQuest(UClass* ToCheckObjectClass);
	void CheckQuest(UClass* ToCheckObjectClass, int AchievedActionType = 0);
	virtual void ManualQuestClear(FString QuestName, int AchieveQuestRequirementIndex) override;
	bool CheckQuest_Cleared(FString QuestName);

	virtual void HoxyPossessClearableQuest(class ACStaticNPC* NPC, TArray<class UCQuestData*>& OutArr) override;
	void ShowDroppedItemList(bool e, class ACDroppedItem* Dropped, class UCInventoryItemData* ItemData);


	void OnInteract();

	void NPCInteract_ShowAndInputReady(class ACStaticNPC* NPC);
	void NPCInteract_Interact();
	void NPCInteract_UnShow();

	void ClimbRopeInteract_ShowAndInputReady(class ACClimbableRope* Rope);
	void ClimbRopeInteract_Interact();
	void ClimbRopeInteract_Move(FVector& NextTickClimbPos, bool& Result, bool IsUpWard);

	void JumpPointsInteract_ShowAndInputReady(class ACJumpPoints* Jumppoints, int JumpPoint);
	void JumpPointsInteract_Interact();

	void PickUpItemInteract_ShowAndInputReady();
	void PickUpItemInteract_Interact();
	//Die UI On
	void CharacterDied(bool b);

	//Teleport Map Select
	virtual void SetSelectedPortal(int ArrIndex) override;
	virtual UINT32 IsPossesQuestCleared(FString QuestName) override;
	virtual void MoveQuestToClearedByQuestName(FString QuestName) override;
	virtual void RemoveQuest(UObject* QuestDat) override;
	virtual bool IsQualifiedQuest(TArray<FString> RequiredQuestsArr) override;

	virtual void EquippedItemStat(struct ItemStat& SumItemStat) override;
	//Also Remove Item From Character
	virtual bool IsSocketEmpty(int ItemType) override;

	virtual void SaveGame(int SlotIndex) override;
	virtual void SaveGame(TArray<uint8>& MemoryAddress) override;
	virtual void LoadGame(int32 SaveSlot) override;
	virtual void LoadGame(TArray<uint8> MemoryAddress) override;

	virtual void DragInItem(class UCInventoryItemData* ToDragItem) override;
	virtual void DragItem(FVector2D WidgetTranslation) override;
	virtual void DragItem() override;
	virtual void DragOutItem() override;
	virtual class UCInventoryItemData* GetQuickSlot() override;

// Battle Staff UI
	virtual void SetBattleVIsibility(bool e) override;
	virtual void SetBruteMode(bool e) override;
	virtual void SetBruteGauge(float Percent) override;
	virtual void SetBruteCooldown(float Percent) override;
	virtual void SetBruteCooldownParam(float MaxCooldown) override;

// Rifle Staff UI
	virtual void SetAimVisibility(bool e) override;
	virtual void SetAimSpriteColorOverlay(float Index) override;
	virtual bool GetWeaponChangeReady() override;
	virtual void SetAimSpriteBlur(float NewBlur) override;
	virtual void SetAimProgressBarPercent(float NewPercent) override;
	virtual void SetRifleSelectCylinder(FVector Bullets, FVector WeaponDisplaySequence) override;
	virtual void DoRifleSelectBarrelRoll() override;
};

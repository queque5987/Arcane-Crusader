// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CUserWidget_InputDisabled.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Components/ListView.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "ITeleportNPC.h"
#include "CNPCConversation.generated.h"

UCLASS()
class MMB_API UCNPCConversation : public UUserWidget //, public IUserObjectListEntry
{
	GENERATED_BODY()

	class ACStaticNPC* NPC;
public:

	void SetNPCName(FText e) { NPCName->SetText(e); }
	void SetNPCLine(FText e) { NPCLine->SetText(e); }
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> NPCLineBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NPCName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NPCLine;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnYes;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBtnYes;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnNo;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBtnNo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnShopIn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBtnShopIn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnQuest;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBtnQuest;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnNext;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBtnNext;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnLeave;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBtnLeave;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ShoppingBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> ItemList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnShopClose;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ShoppingBox_Inventory;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> ItemList_Inventory;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerGold;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnShopBuy;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnShopSell;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SwingbyAlertBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SwingbyLine;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> TeleportableListBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> TeleportableMapList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnTeleportClose;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnTeleportSend;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> QuestListBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> QuestList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnQuestLeave;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnQuestAccept;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> QuestRewardBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnQuestRewardAccept;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> QuestRewardItemList;
	

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	void SetNPC(class ACStaticNPC* e) { NPC = e; }
	class ACStaticNPC* GetNPC() { return NPC; }
	void SetItemList(class ACStaticNPC** e);
	void SetLoadedMapIndex(int e) { LoadedMapIndex = e; }

	UFUNCTION()
	void OnButtonYesClicked();
	UFUNCTION()
	void OnButtonNoClicked();
	UFUNCTION()
	void OnButtonShopCloseClicked();
	UFUNCTION()
	void OnButtonShopInClicked();
	UFUNCTION()
	void OnButtonNextClicked();
	UFUNCTION()
	void OnButtonQuestClicked();
	UFUNCTION()
	void OnButtonLeaveClicked();
	UFUNCTION()
	void OnButtonTeleportClicked();
	UFUNCTION()
	void OnButtonTeleportCloseClicked();
	UFUNCTION()
	void OnButtonTeleportSendClicked();
	UFUNCTION()
	void OnButtonBuyClicked();
	UFUNCTION()
	void OnButtonSellClicked();
	UFUNCTION()
	void OnButtonQuestLeaveClicked();
	UFUNCTION()
	void OnButtonQuestAcceptClicked();
	UFUNCTION()
	void OnButtonQuestRewardAcceptClicked();

	void AlertSwingby(float e, FText Line);
	UFUNCTION()
	void ShutdownSwingby();
	void SetDialogues(TArray<struct FNPCDialoguesRow*> e) { Dialogues = e; }

	TArray<FTeleportableMapTableRow*> Arr;

	bool IsOnShop();
	void ShoppingBox_LoadPlayerInventory();
	void QuestBox_LoadNPCQuest();

	void SetSelectedButton(UUserWidget* SelectedButton);
private:

	bool AllowInput;

	const int NPC_LINE			= 0;
	const int BUTTON_NEXT		= 1;
	const int BUTTON_YES		= 2;
	const int BUTTON_NO			= 3;
	const int BUTTON_SHOP		= 4;
	const int BUTTON_QUEST		= 5;
	const int BUTTON_LEAVE		= 6;
	const int REWARD_GIVE		= 7;
	const int MAX_BUTTON_NUM	= 8;

	int BUTTON_NEXT_POSTLINE;
	int BUTTON_YES_POSTLINE;
	int BUTTON_NO_POSTLINE;
	int BUTTON_SHOP_POSTLINE;
	int BUTTON_QUEST_POSTLINE;
	int BUTTON_LEAVE_POSTLINE;
	int BUTTON_REWARD_POSTLINE;
	//int BUTTON_TELEPORT_POSTLINE;	//DEPRECATED

	bool IsQuest_NotTeleport = true;

	FQuestsRow* LoadedQuest;
	//FQuestsRow* LoadedQuestData;
	int LoadedMapIndex = -1;

	TArray<FWidgetTransform> BtnTransforms;

	TArray<int> NextBtnStates;
	float InSwingbyTime;
	float InSwingbyClock;
	FTimerHandle SwingbyTimerHandle;
	TArray<struct FNPCDialoguesRow*> Dialogues;
	void SetLineFromDialogues(int e);
	void SwitchQuestMode(bool e);

	UUserWidget* SelectedButton_ToBuy;
	UUserWidget* SelectedButton_ToSell;
	UUserWidget* SelectedButton_Quest;

	void SetSelectedShopItem(UUserWidget* SelectedButton);
	void SetSelectedQuest(UUserWidget* SelectedButton);

	void OpenQuestRewardBox();

	void ResetSelectedWidgets();
};

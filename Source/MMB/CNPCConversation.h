// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CUserWidget_InputDisabled.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
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
	//FSimpleDelegate DELEGATE_BUTTON_NEXT;
	//FSimpleDelegate DELEGATE_BUTTON_YES;
	//FSimpleDelegate DELEGATE_BUTTON_NO;
	//FSimpleDelegate DELEGATE_BUTTON_SHOP;
	//FSimpleDelegate DELEGATE_BUTTON_QUEST;
	//FSimpleDelegate DELEGATE_BUTTON_LEAVE;
	//FSimpleDelegate DELEGATE_BUTTON_TELEPORT;

	//TArray<FSimpleDelegate*> ButtonDelegates = {
	//	nullptr,
	//	&DELEGATE_BUTTON_NEXT,
	//	&DELEGATE_BUTTON_YES,
	//	&DELEGATE_BUTTON_NO,
	//	&DELEGATE_BUTTON_SHOP,
	//	&DELEGATE_BUTTON_QUEST,
	//	&DELEGATE_BUTTON_LEAVE,
	//	&DELEGATE_BUTTON_TELEPORT
	//};

	void SetNPCName(FText e) { NPCName->SetText(e); }
	void SetNPCLine(FText e) { NPCLine->SetText(e); }
	
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "User Interface", meta = (Keywords = "Begin Play"))
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//UClass* ButtonClass;
	//UCNPCConversation(const FObjectInitializer& ObjectInitializer);
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

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UButton> BtnTeleport;
	
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

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UTileView> ButtonsBox;

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	void SetNPC(class ACStaticNPC* e) { NPC = e; }
	class ACStaticNPC* GetNPC() { return NPC; }
	void SetItemList(class ACStaticNPC** e);

	//typedef void (UCNPCConversation::* YesFunction)(void);
	//typedef void (UCNPCConversation::* NoFunction)(void);
	//YesFunction BtnYesPtr;
	//NoFunction BtnNoPtr;

	//void (*BtnYesPtr)();
	//void (*BtnNoPtr)();

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

	void AlertSwingby(float e, FText Line);
	UFUNCTION()
	void ShutdownSwingby();
	void SetDialogues(TArray<struct FNPCDialoguesRow*> e) { Dialogues = e; }

	TArray<FTeleportableMapTableRow*> Arr;

private:

	bool AllowInput;

	const int NPC_LINE			= 0;
	const int BUTTON_NEXT		= 1;
	const int BUTTON_YES		= 2;
	const int BUTTON_NO			= 3;
	const int BUTTON_SHOP		= 4;
	const int BUTTON_QUEST		= 5;
	const int BUTTON_LEAVE		= 6;
	const int BUTTON_TELEPORT	= 7;
	const int MAX_BUTTON_NUM	= 8;

	int BUTTON_NEXT_POSTLINE;
	int BUTTON_YES_POSTLINE;
	int BUTTON_NO_POSTLINE;
	int BUTTON_SHOP_POSTLINE;
	int BUTTON_QUEST_POSTLINE;
	int BUTTON_LEAVE_POSTLINE;
	int BUTTON_TELEPORT_POSTLINE;

	bool IsQuest_NotTeleport = true;

	//TArray<int*> ButtonPostlines = {
	//	nullptr,
	//	&BUTTON_NEXT_POSTLINE,
	//	&BUTTON_YES_POSTLINE,
	//	&BUTTON_NO_POSTLINE,
	//	&BUTTON_SHOP_POSTLINE,
	//	&BUTTON_QUEST_POSTLINE,
	//	&BUTTON_LEAVE_POSTLINE,
	//	&BUTTON_TELEPORT_POSTLINE
	//};

	FQuestsRow* LoadedQuest;

	TArray<FWidgetTransform> BtnTransforms;

	TArray<int> NextBtnStates;
	float InSwingbyTime;
	float InSwingbyClock;
	FTimerHandle SwingbyTimerHandle;
	TArray<struct FNPCDialoguesRow*> Dialogues;
	void SetLineFromDialogues(int e);
	void SwitchQuestMode(bool e);
};

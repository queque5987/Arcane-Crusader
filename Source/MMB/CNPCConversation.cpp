﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CNPCConversation.h"
#include "CNPCConversationButton.h"
#include "CNPCConversationButtonData.h"
#include "CTeleportableMapData.h"
#include "IPortalNPC.h"
#include "CListedQuest.h"
#include "CShopItem.h"
#include "CGameInstance.h"
#include "CEnemy_TerrorBringer.h"
#include "CEnemy_Nightmare.h"
#include "CDynamicNPC.h"
//#include "Async/Async.h"
#include "FMonsterConfigure.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CUserWidget_ListedStage.h"

void UCNPCConversation::NativeConstruct()
{
	Super::NativeConstruct();

	BtnYes->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonYesClicked);
	BtnNo->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonNoClicked);
	BtnShopIn->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonShopInClicked);
	BtnShopClose->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonShopCloseClicked);
	BtnNext->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonNextClicked);
	BtnQuest->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonQuestClicked);
	BtnLeave->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonLeaveClicked);
	//BtnTeleport->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonTeleportClicked);

	//Btn_Map_L->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonMapLeftClicked);
	//Btn_Map_R->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonMapRightClicked);
	//Btn_Monster_L->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonMonsterLeftClicked);
	//Btn_Monster_R->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonMonsterRightClicked);

	BtnTeleportClose->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonTeleportCloseClicked);
	BtnTeleportSend->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonTeleportSendClicked);

	BtnShopSell->OnReleased.AddDynamic(this, &UCNPCConversation::OnButtonSellClicked);
	BtnShopBuy->OnReleased.AddDynamic(this, &UCNPCConversation::OnButtonBuyClicked);

	BtnQuestLeave->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonQuestLeaveClicked);
	BtnQuestAccept->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonQuestAcceptClicked);
	BtnQuestRewardAccept->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonQuestRewardAcceptClicked);
	
	ShoppingBox->SetVisibility(ESlateVisibility::Hidden);

	SwingbyAlertBox->SetVisibility(ESlateVisibility::Hidden);
	SwingbyAlertBox->SetRenderOpacity(0.f);
	InSwingbyTime = 0.f;
	InSwingbyClock = 0.f;

	TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);
	QuestListBox->SetVisibility(ESlateVisibility::Hidden);
	QuestRewardBox->SetVisibility(ESlateVisibility::Hidden);

	// Material Interface Instance Load
	if (Teleportable_MapPreview != nullptr) MapSelectionMaterialInstance = Teleportable_MapPreview->GetDynamicMaterial();
	if (MapSelectionMaterialInstance == nullptr) UE_LOG(LogTemp, Error, TEXT("MapSelectionMaterialInstance Not Found"));
	if (MonsterSelection != nullptr) MonsterSelectionMaterialInstance = MonsterSelection->GetDynamicMaterial();
	if (MonsterSelectionMaterialInstance == nullptr) UE_LOG(LogTemp, Error, TEXT("MonsterSelectionMaterialInstance Not Found"));

	StageList->SetSelectionMode(ESelectionMode::Single);
}

void UCNPCConversation::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(PCC->GetCharacter()))
		{
			if (!AllowInput && !PC->GetState(PLAYER_UI_INTERACTING))
			{
				SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}

	if (InSwingbyTime > 0.f)
	{
		float CurrOpacity = SwingbyAlertBox->GetRenderOpacity();
		float d = CurrOpacity;
		if		(InSwingbyClock < InSwingbyTime / 5 && CurrOpacity < 1.f)
		{
			d = CurrOpacity + InDeltaTime * 6 / InSwingbyTime;
		}
		else if (InSwingbyClock > InSwingbyTime / 2 && CurrOpacity > 0.f)
		{
			d = CurrOpacity - InDeltaTime * 2 / InSwingbyTime;
		}
		if		(d < 0.f) d = 0.f;
		else if (d > 1.f) d = 1.f;
		SwingbyAlertBox->SetRenderOpacity(d);
	}
	InSwingbyClock += InDeltaTime;
}

void UCNPCConversation::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(PCC->GetCharacter()))
		{
			PC->SetState(PLAYER_UI_INTERACTING, InVisibility == ESlateVisibility::Hidden ? false : true);
		}
	}

	//if (NPC != nullptr && InVisibility == ESlateVisibility::Visible)
	if (InVisibility == ESlateVisibility::Visible)
	{
		if (GetWorld()->GetTimerManager().TimerExists(SwingbyTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(SwingbyTimerHandle);
			AllowInput = false;
			InSwingbyTime = 0.f;
		}
		//ItemList->ClearListItems();
		//if (NPC != nullptr) NPC->SetNPCConversationItemList(ItemList);
		ShoppingBox->SetVisibility(ESlateVisibility::Hidden);
		NPCLineBox->SetVisibility(ESlateVisibility::Visible);
		TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);
		QuestListBox->SetVisibility(ESlateVisibility::Hidden);
		QuestRewardBox->SetVisibility(ESlateVisibility::Hidden);
		SetLineFromDialogues(0);
	}
}

void UCNPCConversation::SetNPC(ACStaticNPC* e)
{
	NPC = e;
	PlayNPCAnimation(4);
}

void UCNPCConversation::SetItemList(ACStaticNPC** e)
{
	ItemList->ClearListItems();
	if(e != nullptr)
	{
		ACStaticNPC* npc = *e;
		for (auto& ta : npc->GetItemList()) 
		{
			ItemList->AddItem(ta);
		}
	}
}

void UCNPCConversation::SetLoadedMapIndex(int e)
{
	LoadedMapIndex = e;

	//TArray<UUserWidget*> tempMaps = TeleportableMapList->GetDisplayedEntryWidgets();
	//for (int i = 0; i < tempMaps.Num(); i++)
	//{
	//	if (i == e) continue;
	//	IIWidgetInteract* IW = Cast<IIWidgetInteract>(tempMaps[i]);
	//	if (IW == nullptr) continue;
	//	IW->SwitchPressed(false);
	//}
}

void UCNPCConversation::OnButtonYesClicked()
{
	//Quest Select Mode
	if (SelectedButton_Quest != nullptr)
	{
		PlayNPCAnimation(2);
		UCListedQuest* ListedQuest = Cast<UCListedQuest>(SelectedButton_Quest);
		if (ListedQuest == nullptr) return;
		UCQuestData* QuestData = Cast<UCQuestData>(ListedQuest->GetQuestData());
		//QuestData->SetGivenNPC(NPC);
		if (QuestData == nullptr) return;

		if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
		{
			//PCC->AddQuest(LoadedQuest);
			PCC->AddQuest(QuestData);
			SelectedButton_Quest = nullptr;
			//LoadedQuest = nullptr;

			SetLineFromDialogues(BUTTON_YES_POSTLINE);
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("QUEST NOT SELECTED ERORR"));
		OnButtonLeaveClicked();
	}
	else // Teleport Map Select Mode
	{
		if (IIPortalNPC* TNPC = Cast<IIPortalNPC>(NPC))
		{
			SelectableMapArr.Empty();
			TNPC->GetTeleportableMaps(SelectableMapArr);

			//SetSelectedMapIndex(0.f);
			//SetSelectedMonsterIndex(0.f);

			TeleportableListBox->SetVisibility(ESlateVisibility::Visible);

			if (SelectableMapArr.Num() > 1)
			{
				for (FTeleportableMapMonsterTableRow* SelectableMap : SelectableMapArr)
				{
					UCTeleportableMapData* temp = NewObject<UCTeleportableMapData>(this, UCTeleportableMapData::StaticClass(), SelectableMap->DisplayLevelName);
					StageList->AddItem(temp);
				}
			}
		}
		
		if (BUTTON_YES_POSTLINE == Dialogues.Num())
		{
			OnLoadingScreenSet.Broadcast("Level_Town");
			UGameplayStatics::OpenLevel(this, "Level_Town");
			UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());
			IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
			if (PCC != nullptr)
			{
				if (GI->SelectedSaveSlot < 0) PCC->SaveGame(GI->TempSaveFileAddress);
				else PCC->SaveGame(GI->SelectedSaveSlot);
			}

			//UE_LOG(LogTemp, Log, TEXT("TODO Teleport Immediate To : %s"), *SelectableMapArr[SelectedMapIndex]->LevelName.ToString());
		}
		SetLineFromDialogues(BUTTON_YES_POSTLINE);
	}
}

void UCNPCConversation::OnButtonNoClicked()
{
	PlayNPCAnimation(3);
	SelectedButton_Quest = nullptr;
	//LoadedQuest = nullptr;
	SetLineFromDialogues(BUTTON_NO_POSTLINE);
}

void UCNPCConversation::OnButtonShopCloseClicked()
{
	PlayNPCAnimation(1);
	SetLineFromDialogues(0);
	ShoppingBox->SetVisibility(ESlateVisibility::Hidden);
	ResetSelectedWidgets();
	//SetSelectedShopItem(nullptr);
}

void UCNPCConversation::OnButtonShopInClicked()
{
	PlayNPCAnimation(0);
	SetLineFromDialogues(BUTTON_SHOP_POSTLINE);
	ShoppingBox->SetVisibility(ESlateVisibility::Visible);
	ShoppingBox_LoadPlayerInventory();
	SetSelectedShopItem(nullptr);
	ItemList->ClearListItems();
	if (NPC != nullptr) NPC->SetNPCConversationItemList(ItemList);
}

void UCNPCConversation::OnButtonNextClicked()
{
	PlayNPCAnimation(1);
	SetLineFromDialogues(BUTTON_NEXT_POSTLINE);
}

void UCNPCConversation::OnButtonQuestClicked()
{
	PlayNPCAnimation(1);
	SetLineFromDialogues(BUTTON_QUEST_POSTLINE);

	QuestListBox->SetVisibility(ESlateVisibility::Visible);
	QuestBox_LoadNPCQuest();

	//if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
	//{
	//	TArray<FQuestsRow*> Quests = NPC->GetQuest();
	//	if (Quests.Num() >= 1) LoadedQuest = Quests[0];

	//	// TO DO : Select Quest Among Quests Arr //
	//}
}

void UCNPCConversation::OnButtonLeaveClicked()
{
	PlayNPCAnimation(4);
	ResetSelectedWidgets();
	if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
	{
		UE_LOG(LogTemp, Log, TEXT("Close"));
		PCC->SetNPCConversationVisibility(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Close Failed"));
	}
}

//Depreated
void UCNPCConversation::OnButtonTeleportClicked()
{
	//SetLineFromDialogues(BUTTON_TELEPORT_POSTLINE);
	//TeleportableListBox->SetVisibility(ESlateVisibility::Visible);
}

void UCNPCConversation::OnButtonMapLeftClicked()
{
	if (SelectableMapArr.IsEmpty()) return;
	
	SetSelectedMapIndex(
		FMath::FloorToInt32(SelectedMapIndex - 1.f) + SelectableMapArr.Num() % SelectableMapArr.Num()
	);
	UE_LOG(LogTemp, Log, TEXT("OnButtonMapLeftClicked : Change To %d"), SelectedMapIndex);
}

void UCNPCConversation::OnButtonMapRightClicked()
{
	if (SelectableMapArr.IsEmpty()) return;
	UE_LOG(LogTemp, Log, TEXT("OnButtonMapRightClicked : Change To %d"), (FMath::FloorToInt32(SelectedMapIndex) + 1) % (SelectableMapArr.Num()));
	SetSelectedMapIndex((FMath::FloorToInt32(SelectedMapIndex) + 1) % (SelectableMapArr.Num()));
}

void UCNPCConversation::OnButtonMonsterLeftClicked()
{
	if (SelectableMapArr.IsEmpty()) return;
	if (!SelectableMapArr.IsValidIndex(SelectedMapIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("SelectedMapIndex Is Invalid"));
		return;
	}
	int32 SpawnableMonsterCount = SelectableMapArr[SelectedMapIndex]->SpawnableMonsters.Num();
	SetSelectedMonsterIndex((FMath::FloorToInt32(SelectedMonsterIndex) - 1 + SpawnableMonsterCount) % SpawnableMonsterCount);
}

void UCNPCConversation::OnButtonMonsterRightClicked()
{
	if (SelectableMapArr.IsEmpty()) return;
	if (!SelectableMapArr.IsValidIndex(SelectedMapIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("SelectedMapIndex Is Invalid"));
		return;
	}
	int32 SpawnableMonsterCount = SelectableMapArr[SelectedMapIndex]->SpawnableMonsters.Num();
	SetSelectedMonsterIndex((FMath::FloorToInt32(SelectedMonsterIndex) + 1) % SpawnableMonsterCount);
}

void UCNPCConversation::OnButtonTeleportCloseClicked()
{
	PlayNPCAnimation(1);
	SetLineFromDialogues(0);
	TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);

	//TArray<UUserWidget*> tempMaps = TeleportableMapList->GetDisplayedEntryWidgets();
	//for (int i = 0; i < tempMaps.Num(); i++)
	//{
	//	IIWidgetInteract* IW = Cast<IIWidgetInteract>(tempMaps[i]);
	//	if (IW == nullptr) continue;
	//	IW->SwitchPressed(false);
	//}
}

void UCNPCConversation::OnButtonTeleportSendClicked()
{
	if (SelectedMapIndex < 0) return;

	PlayNPCAnimation(1);

	FName LoadedMapName = SelectableMapArr[SelectedMapIndex]->LevelName;

	UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());

	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;

	GI->BattleQuestRowIndex = SelectableMapArr[SelectedMapIndex]->QuestIndex;
	GI->StartLevelClock = SelectableMapArr[SelectedMapIndex]->LevelClock;

	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (PCC != nullptr)
	{
		if (GI->SelectedSaveSlot < 0) PCC->SaveGame(GI->TempSaveFileAddress);
		else PCC->SaveGame(GI->SelectedSaveSlot);
	}

	OnLoadingScreenSet.Broadcast(LoadedMapName);
	UGameplayStatics::OpenLevel(this, LoadedMapName);
}

void UCNPCConversation::OnButtonBuyClicked()
{
	PlayNPCAnimation(2);
	if (SelectedButton_ToBuy == nullptr) return;
	UCShopItem* ShopItem = Cast<UCShopItem>(SelectedButton_ToBuy);
	if (ShopItem == nullptr) return;
	ShopItem->BuyItem();
	ShoppingBox_LoadPlayerInventory();
}

void UCNPCConversation::OnButtonSellClicked()
{
	PlayNPCAnimation(2);
	if (SelectedButton_ToSell == nullptr) return;
	UCShopItem* ShopItem = Cast<UCShopItem>(SelectedButton_ToSell);
	if (ShopItem == nullptr) return;
	ShopItem->SellItem();
	ShoppingBox_LoadPlayerInventory();
}

void UCNPCConversation::OnButtonQuestLeaveClicked()
{
	PlayNPCAnimation(1);
	QuestListBox->SetVisibility(ESlateVisibility::Hidden);
	SetLineFromDialogues(0);
	ResetSelectedWidgets();
	//SetSelectedQuest(nullptr);
	//SelectedButton_Quest = nullptr;
}

void UCNPCConversation::OnButtonQuestAcceptClicked()
{
	PlayNPCAnimation(2);
	if (SelectedButton_Quest == nullptr) return;
	UCListedQuest* ListedQuest = Cast<UCListedQuest>(SelectedButton_Quest);
	if (ListedQuest == nullptr) return;
	UCQuestData* QuestData = Cast<UCQuestData>(ListedQuest->GetQuestData());
	if (QuestData == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	//UINT32 QuestState = UIController->IsPossesQuestCleared(QuestData->GetQuestName());

	UINT32 QuestState = ListedQuest->GetQuestState();
	switch (QuestState)
	{
	case(QUEST_CLEARED):
		//Give Reward
		QuestListBox->SetVisibility(ESlateVisibility::Hidden);
		SetLineFromDialogues(QuestData->GetQuestRewardDialogueIndex());
		break;
	case(QUEST_ALREADY_HAVE):
		//Quest Yet UnCleared
		UIController->AddAlert(FText::FromString(TEXT("진행중인 퀘스트입니다.")));
		break;
	case(QUEST_ALEARDY_CLEARED):
		//Already Cleard //TODO
		UIController->AddAlert(FText::FromString(TEXT("이미 완료한 퀘스트입니다.")));
		break;
	case(QUEST_UNQUALIFIED):
		UIController->AddAlert(FText::FromString(TEXT("아직 수행할 수 없는\n 퀘스트입니다.")));
		break;
	case(QUEST_NO_MATCH):
	default:
		QuestListBox->SetVisibility(ESlateVisibility::Hidden);
		SetLineFromDialogues(QuestData->GetQuestDialogueIndex());
		break;
	}

	//if (ClearFlag) SetLineFromDialogues(QuestData->GetQuestRewardDialogueIndex());
	//else SetLineFromDialogues(QuestData->GetQuestDialogueIndex()); 
}

void UCNPCConversation::OnButtonQuestRewardAcceptClicked()
{
	PlayNPCAnimation(2);
	UCListedQuest* ListedQuest = Cast<UCListedQuest>(SelectedButton_Quest);
	if (ListedQuest == nullptr) return;
	UCQuestData* QuestData = Cast<UCQuestData>(ListedQuest->GetQuestData());
	if (QuestData == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	for (UObject* RewardItem : QuestRewardItemList->GetListItems())
	{
		UCInventoryItemData* tempRewardItemData = Cast<UCInventoryItemData>(RewardItem);
		if (tempRewardItemData == nullptr) continue;
		UIController->AddInventoryItem(tempRewardItemData);
	}
	QuestRewardBox->SetVisibility(ESlateVisibility::Hidden);
	QuestRewardItemList->ClearListItems();

	UIController->MoveQuestToClearedByQuestName(QuestData->GetQuestName());
	SetLineFromDialogues(BUTTON_REWARD_POSTLINE);
}

void UCNPCConversation::AlertSwingby(float e, FText Line)
{
	InSwingbyTime = e;
	InSwingbyClock = 0.f;
	SwingbyLine->SetText(Line);

	AllowInput = true;
	SetVisibility(ESlateVisibility::Visible);
	if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(PCC->GetCharacter())) PC->SetState(PLAYER_UI_INTERACTING, false);
	}

	NPCLineBox->SetVisibility(ESlateVisibility::Hidden);
	SwingbyAlertBox->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().ClearTimer(SwingbyTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(SwingbyTimerHandle, this, &UCNPCConversation::ShutdownSwingby, e);
}

void UCNPCConversation::ShutdownSwingby()
{
	SwingbyAlertBox->SetVisibility(ESlateVisibility::Hidden);
	AllowInput = false;

	SetVisibility(ESlateVisibility::Hidden);
	InSwingbyTime = 0.f;
}

bool UCNPCConversation::IsOnShop()
{
	return ShoppingBox->GetVisibility() == ESlateVisibility::Visible ? true : false;
}

void UCNPCConversation::SetSelectedStage(UUserWidget* StageButton)
{
	SelectedStage = (SelectedStage == StageButton) ? nullptr : StageButton;
	if (SelectedStage == nullptr)
	{
		SelectedMapIndex = -1;
		MapSelectionMaterialInstance->SetScalarParameterValue("SelectedMapIndex", -1.f);
	}

	TArray<UUserWidget*> tempArr = StageList->GetDisplayedEntryWidgets();
	for (int i = 0; i < tempArr.Num(); i++)
	{
		UCUserWidget_ListedStage* CWidget = Cast<UCUserWidget_ListedStage>(tempArr[i]);
		if (CWidget != nullptr)
		{
			bool IsIt = (SelectedStage == tempArr[i]) ? true : false;
			CWidget->SwitchPressed(IsIt);
			if (IsIt && (MapSelectionMaterialInstance != nullptr && MonsterSelectionMaterialInstance != nullptr))
			{
				MapSelectionMaterialInstance->SetScalarParameterValue("SelectedMapIndex", SelectableMapArr[i]->TextureArrayIndex);
				MonsterSelectionMaterialInstance->SetScalarParameterValue("SelectedMonsterIndex", SelectableMapArr[i]->MonsterTextureArrayIndex);
				SelectedMapIndex = i;
			}
		}
	}
}

void UCNPCConversation::SetSelectedMapIndex(float NewMapIndex)
{
	//MapSelection
	if (!SelectableMapArr.IsValidIndex(NewMapIndex))
	{
		for (FTeleportableMapMonsterTableRow* Row : SelectableMapArr)
		{
			UE_LOG(LogTemp, Log, TEXT("Map Row : %s"), *Row->DisplayLevelName.ToString());
		}
		UE_LOG(LogTemp, Error, TEXT("SelectedMapIndex Is Invalid"));
		return;
	}
	SelectedMapIndex = NewMapIndex;
	MapSelectionMaterialInstance->SetScalarParameterValue("SelectedMapIndex", SelectedMapIndex);
	SetSelectedMonsterIndex(0.f);
}

void UCNPCConversation::SetSelectedMonsterIndex(float NewMonsterIndex)
{
	//MonsterSelection
	if (!SelectableMapArr.IsValidIndex(SelectedMapIndex))
	{
		for (FTeleportableMapMonsterTableRow* Row : SelectableMapArr)
		{
			UE_LOG(LogTemp, Log, TEXT("Row : %s"), *Row->DisplayLevelName.ToString());
		}
		UE_LOG(LogTemp, Error, TEXT("SelectedMapIndex Is Invalid"));
		return;
	}
	if (!SelectableMapArr[SelectedMapIndex]->SpawnableMonsters.IsValidIndex(NewMonsterIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("SelectedMapIndex Is Invalid"));
		return;
	}
	SelectedMonsterIndex = NewMonsterIndex;
	MonsterSelectionMaterialInstance->SetScalarParameterValue("SelectedMonsterIndex", SelectableMapArr[SelectedMapIndex]->SpawnableMonsterPreviews[SelectedMonsterIndex]);
}

void UCNPCConversation::SetLineFromDialogues(int e)
{

	if (Dialogues.IsValidIndex(e))
	{
		FNPCDialoguesRow* Row = Dialogues[e];
		NPCName->SetText(Row->NPCName);
		NPCLine->SetText(Row->NPCDialogue);

		BUTTON_NEXT_POSTLINE = Row->BUTTON_NEXT_POSTLINE;
		BUTTON_YES_POSTLINE = Row->BUTTON_YES_POSTLINE;
		BUTTON_NO_POSTLINE = Row->BUTTON_NO_POSTLINE;
		BUTTON_SHOP_POSTLINE = Row->BUTTON_SHOP_POSTLINE;
		BUTTON_QUEST_POSTLINE = Row->BUTTON_QUEST_POSTLINE;
		BUTTON_LEAVE_POSTLINE = Row->BUTTON_LEAVE_POSTLINE;
		BUTTON_REWARD_POSTLINE = Row->BUTTON_REWARD_POSTLINE;

		if (BUTTON_REWARD_POSTLINE >= 0) OpenQuestRewardBox();

		BtnNext->SetIsEnabled((BUTTON_NEXT_POSTLINE >= 0) ? true : false);
		BtnYes->SetIsEnabled((BUTTON_YES_POSTLINE >= 0) ? true : false);
		BtnNo->SetIsEnabled((BUTTON_NO_POSTLINE >= 0) ? true : false);
		BtnShopIn->SetIsEnabled((BUTTON_SHOP_POSTLINE >= 0) ? true : false);
		BtnQuest->SetIsEnabled((BUTTON_QUEST_POSTLINE >= 0) ? true : false);
		BtnLeave->SetIsEnabled((BUTTON_LEAVE_POSTLINE >= 0) ? true : false);
	}
}

void UCNPCConversation::SwitchQuestMode(bool e)
{
	if (e)
	{
		BtnShopIn->SetVisibility(ESlateVisibility::Hidden);
		TextBtnYes->SetText(FText::FromString(FString(TEXT("수락하기"))));
		TextBtnNo->SetText(FText::FromString(FString(TEXT("거절하기"))));
		//BtnYesPtr = &UCNPCConversation::BtnYes_Quest;
		//BtnNoPtr = &UCNPCConversation::BtnNo_Quest;
	}
	else
	{
		BtnShopIn->SetVisibility(ESlateVisibility::Visible);
		TextBtnYes->SetText(FText::FromString(FString(TEXT("퀘스트"))));
		TextBtnNo->SetText(FText::FromString(FString(TEXT("떠나기"))));
		//BtnYesPtr = &UCNPCConversation::BtnYes_Normal;
		//BtnNoPtr = &UCNPCConversation::BtnNo_Normal;
	}
}

void UCNPCConversation::SetSelectedShopItem(UUserWidget* SelectedButton)
{
	TArray<UUserWidget*> ItemWidgets = ItemList->GetDisplayedEntryWidgets();
	IIWidgetInteract* tempPressedWidget = nullptr;
	bool flag = false;
	for (UUserWidget* ItemWidget : ItemWidgets)
	{
		IIWidgetInteract* IIWidget = Cast<IIWidgetInteract>(ItemWidget);
		if (IIWidget == nullptr) continue;
		if (ItemWidget == SelectedButton)
		{
			flag = true;
			IIWidget->SwitchPressed(true);
			SelectedButton_ToBuy = SelectedButton;
			continue;
		}
		if (IIWidget->GetbPressed())
		{
			tempPressedWidget = IIWidget;
		}
	}
	if (flag && tempPressedWidget != nullptr) tempPressedWidget->SwitchPressed(false);

	flag = false;
	tempPressedWidget = nullptr;
	ItemWidgets = ItemList_Inventory->GetDisplayedEntryWidgets();
	for (UUserWidget* ItemWidget : ItemWidgets)
	{
		IIWidgetInteract* IIWidget = Cast<IIWidgetInteract>(ItemWidget);
		if (IIWidget == nullptr) continue;
		if (ItemWidget == SelectedButton)
		{
			flag = true;
			IIWidget->SwitchPressed(true);
			SelectedButton_ToSell = SelectedButton;
			continue;
		}
		if (IIWidget->GetbPressed())
		{
			tempPressedWidget = IIWidget;
		}
	}
	if (flag && tempPressedWidget != nullptr) tempPressedWidget->SwitchPressed(false);
}

void UCNPCConversation::SetSelectedQuest(UUserWidget* SelectedButton)
{
	TArray<UUserWidget*> QuestWidgets = QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		IIWidgetInteract* IIWidget = Cast<IIWidgetInteract>(QuestWidget);
		if (IIWidget == nullptr) continue;
		if (QuestWidget == SelectedButton)
		{
			IIWidget->SwitchPressed(true);
			SelectedButton_Quest = SelectedButton;
			continue;
		}
		IIWidget->SwitchPressed(false);
	}
}

void UCNPCConversation::OpenQuestRewardBox()
{
	QuestRewardItemList->ClearListItems();
	QuestRewardBox->SetVisibility(ESlateVisibility::Visible);

	UCListedQuest* QuestWidget = Cast<UCListedQuest>(SelectedButton_Quest);
	if (QuestWidget == nullptr) return;
	UCQuestData* QuestData = Cast<UCQuestData>(QuestWidget->GetListItem());
	if (QuestData == nullptr) return;
	TArray<FName> QuestRewards = QuestData->GetQuestRewards();
	TArray<int> QuestRewardsQ = QuestData->GetQuestRewardsQuantity();

	IIItemManager* ItemManager = Cast<IIItemManager>(GetOwningPlayer()->GetWorld()->GetAuthGameMode());
	for (int i = 0; i < QuestRewards.Num(); i++)
	{
		UCInventoryItemData* ItemData = ItemManager->GetItem(QuestRewards[i], QuestRewardsQ[i]);
		if (QuestRewardsQ[i] > 1) 
		{
			ItemData->SetItemCount(QuestRewardsQ[i]);
		}
		QuestRewardItemList->AddItem(ItemData);
	}
	//for (FName QuestReward : QuestRewards)
	//{
	//	UCInventoryItemData* ItemData = ItemManager->GetItem(QuestReward);
	//	QuestRewardItemList->AddItem(ItemData);
	//}
}

void UCNPCConversation::ResetSelectedWidgets()
{
	if (SelectedButton_ToBuy != nullptr)
	{
		IIWidgetInteract* InteractableWidget = Cast<IIWidgetInteract>(SelectedButton_ToBuy);
		InteractableWidget->SwitchPressed(false);
		SelectedButton_ToBuy = nullptr;
		//for (UUserWidget* DisplayedWidget : ItemList->GetDisplayedEntryWidgets())
		//{
		//	IIWidgetInteract* InteractableWidget = Cast<IIWidgetInteract>(DisplayedWidget);
		//	InteractableWidget->SwitchPressed(false);
		//}
	}

	if (SelectedButton_ToSell != nullptr)
	{
		IIWidgetInteract* InteractableWidget = Cast<IIWidgetInteract>(SelectedButton_ToSell);
		InteractableWidget->SwitchPressed(false);
		SelectedButton_ToSell = nullptr;
	}

	if (SelectedButton_Quest != nullptr)
	{
		IIWidgetInteract* InteractableWidget = Cast<IIWidgetInteract>(SelectedButton_Quest);
		InteractableWidget->SwitchPressed(false);
		SelectedButton_Quest = nullptr;
	}

}

void UCNPCConversation::PlayNPCAnimation(int32 State)
{
	if (NPC == nullptr) return;
	ACDynamicNPC* AnimNPC = Cast<ACDynamicNPC>(NPC);
	if (AnimNPC == nullptr) return;
	AnimNPC->SetNPCAnimation(State);
}

void UCNPCConversation::ShoppingBox_LoadPlayerInventory()
{
	IIPlayerUIController* IController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (IController == nullptr) return;
	IIPlayerState* PC = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	if (PC == nullptr) return;
	ItemList_Inventory->ClearListItems();
	IController->SetShopInventoryItems(ItemList_Inventory);
	PlayerGold->SetText(FText::FromString(FString::FromInt(PC->GetPlayerGold())));
}

void UCNPCConversation::QuestBox_LoadNPCQuest()
{
	QuestList->ClearListItems();

	if (NPC == nullptr) return;
	TArray<FQuestsRow*> ContainingQuests = NPC->GetQuest();

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	//Containing Quest Check
	for (FQuestsRow* ContainingQuest : ContainingQuests)
	{
		UCQuestData* ID = NewObject<UCQuestData>(this, UCQuestData::StaticClass(), FName(ContainingQuest->QuestName));
		if (ID == nullptr) continue; //At Least One Missing

		TArray<FString> RequiredQuests = ContainingQuest->RequiredQuest;

		ID->SetDetails(ContainingQuest);
		QuestList->AddItem(ID);
	}

	TArray<UCQuestData*> OutArr;
	UIController->HoxyPossessClearableQuest(NPC, OutArr);
	for (UCQuestData* ClearableQuest : OutArr)
	{
		QuestList->AddItem(ClearableQuest);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *ClearableQuest->GetQuestName());
	}


	QuestList->RequestRefresh();

	for (UUserWidget* W : QuestList->GetDisplayedEntryWidgets())
	{
		UCListedQuest* ListedQuestWidget = Cast<UCListedQuest>(W);
		if (ListedQuestWidget == nullptr) continue;
		ListedQuestWidget->ResumeButtonStyle();
	}
}

void UCNPCConversation::SetSelectedButton(UUserWidget* SelectedButton)
{
	if (SelectedButton->IsA(UCShopItem::StaticClass())) SetSelectedShopItem(SelectedButton);
	else if (SelectedButton->IsA(UCListedQuest::StaticClass())) SetSelectedQuest(SelectedButton);
	else if (SelectedButton->IsA(UCUserWidget_ListedStage::StaticClass())) SetSelectedStage(SelectedButton);
}

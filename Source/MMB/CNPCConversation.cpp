// Fill out your copyright notice in the Description page of Project Settings.


#include "CNPCConversation.h"
#include "CNPCConversationButton.h"
#include "CNPCConversationButtonData.h"
#include "CTeleportableMapData.h"
#include "IPortalNPC.h"
#include "CListedQuest.h"
#include "CShopItem.h"

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
	BtnTeleportClose->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonTeleportCloseClicked);
	BtnTeleportSend->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonTeleportSendClicked);

	BtnShopSell->OnReleased.AddDynamic(this, &UCNPCConversation::OnButtonSellClicked);
	BtnShopBuy->OnReleased.AddDynamic(this, &UCNPCConversation::OnButtonBuyClicked);

	BtnQuestLeave->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonQuestLeaveClicked);
	BtnQuestAccept->OnClicked.AddDynamic(this, &UCNPCConversation::OnButtonQuestAcceptClicked);

	ShoppingBox->SetVisibility(ESlateVisibility::Hidden);

	SwingbyAlertBox->SetVisibility(ESlateVisibility::Hidden);
	SwingbyAlertBox->SetRenderOpacity(0.f);
	InSwingbyTime = 0.f;
	InSwingbyClock = 0.f;

	TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);
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

	if (NPC != nullptr && InVisibility == ESlateVisibility::Visible)
	{
		if (GetWorld()->GetTimerManager().TimerExists(SwingbyTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(SwingbyTimerHandle);
			AllowInput = false;
			InSwingbyTime = 0.f;
		}
		ItemList->ClearListItems();
		NPC->SetNPCConversationItemList(ItemList);
		ShoppingBox->SetVisibility(ESlateVisibility::Hidden);
		NPCLineBox->SetVisibility(ESlateVisibility::Visible);
		TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);
		QuestListBox->SetVisibility(ESlateVisibility::Hidden);
		//SwingbyAlertBox->SetVisibility(ESlateVisibility::Hidden);
		SetLineFromDialogues(0);
	}
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

void UCNPCConversation::OnButtonYesClicked()
{
	//Quest Select Mode
	//if (LoadedQuest != nullptr)
	if (SelectedButton_Quest != nullptr)
	{
		UCListedQuest* ListedQuest = Cast<UCListedQuest>(SelectedButton_Quest);
		if (ListedQuest == nullptr) return;
		UCQuestData* QuestData = Cast<UCQuestData>(ListedQuest->GetQuestData());
		QuestData->SetGivenNPC(NPC);
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
		TeleportableMapList->ClearListItems();
		SetLineFromDialogues(BUTTON_YES_POSTLINE);

		if (IIPortalNPC* TNPC = Cast<IIPortalNPC>(NPC))
		{
			Arr.Empty();
			TNPC->GetTeleportableMaps(Arr);
			UCTeleportableMapData* ID;
			if (Arr.Num() > 0)
			{
				int temp = 0;
				for (FTeleportableMapTableRow* R : Arr)
				{
					ID = NewObject<UCTeleportableMapData>(this, UCTeleportableMapData::StaticClass(), R->LevelName);
					if (ID != nullptr)
					{
						UObject* L = StaticLoadObject(UWorld::StaticClass(), nullptr, *R->Level);
						//UWorld* L = LoadObject<UWorld*>(*R->Level);
						if (UWorld* W = Cast<UWorld>(L))
						{
							ID->SetDestLevel(W);
						}
						ID->SetDestLevelName(R->LevelName);
						ID->SetDestLocation(R->Pos);
						ID->SetArrIndex(temp++);
						ID->SetPreviewSlateBrush(R->PreviewSlateBrush);
						ID->SetRelatedQuestIndex(R->RelatedQuestIndex);
						TeleportableMapList->AddItem(ID);
					}
				}
			}
		}

		TeleportableListBox->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCNPCConversation::OnButtonNoClicked()
{
	SelectedButton_Quest = nullptr;
	//LoadedQuest = nullptr;
	SetLineFromDialogues(BUTTON_NO_POSTLINE);
}

void UCNPCConversation::OnButtonShopCloseClicked()
{
	SetLineFromDialogues(0);
	ShoppingBox->SetVisibility(ESlateVisibility::Hidden);
	SetSelectedShopItem(nullptr);
}

void UCNPCConversation::OnButtonShopInClicked()
{
	SetLineFromDialogues(BUTTON_SHOP_POSTLINE);
	ShoppingBox->SetVisibility(ESlateVisibility::Visible);
	ShoppingBox_LoadPlayerInventory();
	SetSelectedShopItem(nullptr);
	//SelectedButton_ToBuy = nullptr;
	//SelectedButton_ToSell = nullptr;
}

void UCNPCConversation::OnButtonNextClicked()
{
	SetLineFromDialogues(BUTTON_NEXT_POSTLINE);
}

void UCNPCConversation::OnButtonQuestClicked()
{
	SetLineFromDialogues(BUTTON_QUEST_POSTLINE);

	QuestBox_LoadNPCQuest();

	QuestListBox->SetVisibility(ESlateVisibility::Visible);
	//if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
	//{
	//	TArray<FQuestsRow*> Quests = NPC->GetQuest();
	//	if (Quests.Num() >= 1) LoadedQuest = Quests[0];

	//	// TO DO : Select Quest Among Quests Arr //
	//}
}

void UCNPCConversation::OnButtonLeaveClicked()
{
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

//Depreated?
void UCNPCConversation::OnButtonTeleportClicked()
{
	SetLineFromDialogues(BUTTON_TELEPORT_POSTLINE);
	TeleportableListBox->SetVisibility(ESlateVisibility::Visible);
}

void UCNPCConversation::OnButtonTeleportCloseClicked()
{
	SetLineFromDialogues(BUTTON_TELEPORT_POSTLINE);
	TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);
}

void UCNPCConversation::OnButtonTeleportSendClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Player Teleport To : Somewhere"), );
	if (TeleportableMapList->GetNumItems() > LoadedMapIndex && LoadedMapIndex >= 0)
	{
		UCTeleportableMapData* LoadedMap = Cast<UCTeleportableMapData>(TeleportableMapList->GetItemAt(LoadedMapIndex));
		
		if (GetOwningPlayer()->GetWorld()->GetName() == LoadedMap->GetDestLevel()->GetMapName())
		{
			//Just Location
			UE_LOG(LogTemp, Log, TEXT("Teleporting to %s At %s"),
				*LoadedMap->GetDestLevel()->GetMapName(),
				*LoadedMap->GetDestLocation().ToString()
			);

			AController* ACC = GetOwningPlayer();
			if (ACC == nullptr) return;
			ACharacter* AC = ACC->GetCharacter();
			if (AC == nullptr) return;
			AC->SetActorLocation(LoadedMap->GetDestLocation());

			int RelatedQuestIndex = LoadedMap->GetRelatedQuestIndex();
			if (RelatedQuestIndex < 0)
			{
				OnButtonLeaveClicked();
				return;
			}
			//If With Quest
			TArray<FQuestsRow*> Quests = NPC->GetQuest();
			if (!Quests.IsValidIndex(RelatedQuestIndex))
			{
				OnButtonLeaveClicked();
				return;
			}
			if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
			{
				FQuestsRow* Quest = Quests[RelatedQuestIndex];
				if (Quest != nullptr)
				{
					PCC->AddQuest(Quest);
				}
			}

			OnButtonLeaveClicked();
		}
		else
		{
			//Load Level
			//Move to Pos
		}
	}
	// TO Do : Move to Selected Map
}

void UCNPCConversation::OnButtonBuyClicked()
{
	if (SelectedButton_ToBuy == nullptr) return;
	UCShopItem* ShopItem = Cast<UCShopItem>(SelectedButton_ToBuy);
	if (ShopItem == nullptr) return;
	ShopItem->BuyItem();
}

void UCNPCConversation::OnButtonSellClicked()
{
	if (SelectedButton_ToSell == nullptr) return;
	UCShopItem* ShopItem = Cast<UCShopItem>(SelectedButton_ToSell);
	if (ShopItem == nullptr) return;
	ShopItem->SellItem();
}

void UCNPCConversation::OnButtonQuestLeaveClicked()
{
	QuestListBox->SetVisibility(ESlateVisibility::Hidden);
	SetLineFromDialogues(0);
	SetSelectedQuest(nullptr);
	//SelectedButton_Quest = nullptr;
}

void UCNPCConversation::OnButtonQuestAcceptClicked()
{
	QuestListBox->SetVisibility(ESlateVisibility::Hidden);

	if (SelectedButton_Quest == nullptr) return;
	UCListedQuest* ListedQuest = Cast<UCListedQuest>(SelectedButton_Quest);
	if (ListedQuest == nullptr) return;
	UCQuestData* QuestData = Cast<UCQuestData>(ListedQuest->GetQuestData());
	if (QuestData == nullptr) return;
	//LoadedQuestData = QuestData;
	SetLineFromDialogues(QuestData->GetQuestDialogueIndex());
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

void UCNPCConversation::SetLineFromDialogues(int e)
{

	if (Dialogues.IsValidIndex(e))
	{
		FNPCDialoguesRow* Row = Dialogues[e];
		NPCName->SetText(Row->NPCName);

		TArray<FString> out;
		const TCHAR* d[] = { TEXT("//") };
		Row->NPCDialogue.ToString().ParseIntoArray(out, d, 1);
		out.SetNum(MAX_BUTTON_NUM+1);
		UE_LOG(LogTemp, Log, TEXT("Line : %s"), *out[NPC_LINE]);

		NPCLine->SetText(FText::FromString(out[NPC_LINE]));

		//int TransformPrior = 0;

		BUTTON_NEXT_POSTLINE =		(FCString::Atoi(*out[BUTTON_NEXT]));
		BUTTON_YES_POSTLINE =		(FCString::Atoi(*out[BUTTON_YES]));
		BUTTON_NO_POSTLINE =		(FCString::Atoi(*out[BUTTON_NO]));
		BUTTON_SHOP_POSTLINE =		(FCString::Atoi(*out[BUTTON_SHOP]));
		BUTTON_QUEST_POSTLINE =		(FCString::Atoi(*out[BUTTON_QUEST]));
		BUTTON_LEAVE_POSTLINE =		(FCString::Atoi(*out[BUTTON_LEAVE]));
		BUTTON_TELEPORT_POSTLINE =	(FCString::Atoi(*out[BUTTON_TELEPORT]));

		//TArray<UUserWidget*> Ws = ButtonsBox->GetDisplayedEntryWidgets();
		////UE_LOG(LogTemp, Log, TEXT("Widgets : %d"), Ws.Num());
		//for (int i = 0; i < Ws.Num(); i++)
		//{
		//	Ws[i]->SetVisibility((*ButtonPostlines[i+1] >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		//	UE_LOG(LogTemp, Log, TEXT("%s : %d"), *Ws[i]->GetName(), *ButtonPostlines[i + 1]);
		//}

		BtnNext->		SetIsEnabled((BUTTON_NEXT_POSTLINE >= 0)		? true : false);
		BtnYes->		SetIsEnabled((BUTTON_YES_POSTLINE >= 0)			? true : false);
		BtnNo->			SetIsEnabled((BUTTON_NO_POSTLINE >= 0)			? true : false);
		BtnShopIn->		SetIsEnabled((BUTTON_SHOP_POSTLINE >= 0)		? true : false);
		BtnQuest->		SetIsEnabled((BUTTON_QUEST_POSTLINE >= 0)		? true : false);
		BtnLeave->		SetIsEnabled((BUTTON_LEAVE_POSTLINE >= 0)		? true : false);
		//BtnTeleport->	SetIsEnabled((BUTTON_TELEPORT_POSTLINE >= 0)	? true : false);

		IsQuest_NotTeleport = (BUTTON_QUEST_POSTLINE >= 0) ? true : false;
		UE_LOG(LogTemp, Log, TEXT("IsQuest_NotTeleport : %s"), IsQuest_NotTeleport ? TEXT("True") : TEXT("False"));
		//BtnNext->		SetRenderScale((BUTTON_NEXT_POSTLINE >= 0)		? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);
		//BtnYes->		SetRenderScale((BUTTON_YES_POSTLINE >= 0)		? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);
		//BtnNo->SetRenderScale((BUTTON_NO_POSTLINE >= 0) ? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);
		//BtnShopIn->SetRenderScale((BUTTON_SHOP_POSTLINE >= 0) ? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);
		//BtnQuest->SetRenderScale((BUTTON_QUEST_POSTLINE >= 0) ? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);
		//BtnLeave->SetRenderScale((BUTTON_LEAVE_POSTLINE >= 0) ? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);
		//BtnTeleport->SetRenderScale((BUTTON_TELEPORT_POSTLINE >= 0) ? FVector2D(1.f, 1.f) : FVector2D::ZeroVector);

		//BtnNext->SetVisibility	((BUTTON_NEXT_POSTLINE	 >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		//BtnYes->SetVisibility	((BUTTON_YES_POSTLINE	 >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		//BtnNo->SetVisibility	((BUTTON_NO_POSTLINE	 >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		//BtnShopIn->SetVisibility((BUTTON_SHOP_POSTLINE	 >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		//BtnQuest->SetVisibility	((BUTTON_QUEST_POSTLINE	 >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		//BtnLeave->SetVisibility	((BUTTON_LEAVE_POSTLINE	 >= 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
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

void UCNPCConversation::ShoppingBox_LoadPlayerInventory()
{
	IIPlayerUIController* IController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (IController == nullptr) return;
	ItemList_Inventory->ClearListItems();
	IController->SetShopInventoryItems(ItemList_Inventory);
}

void UCNPCConversation::QuestBox_LoadNPCQuest()
{
	if (NPC == nullptr) return;
	TArray<FQuestsRow*> ContainingQuests = NPC->GetQuest();
	for (FQuestsRow* ContainingQuest : ContainingQuests)
	{
		UCQuestData* ID = NewObject<UCQuestData>(this, UCQuestData::StaticClass(), FName(ContainingQuest->QuestName));
		if (ID == nullptr) continue;
		ID->SetDetails(ContainingQuest);
		QuestList->AddItem(ID);
	}
}

void UCNPCConversation::SetSelectedButton(UUserWidget* SelectedButton)
{
	if (SelectedButton->IsA(UCShopItem::StaticClass())) SetSelectedShopItem(SelectedButton);
	else if (SelectedButton->IsA(UCListedQuest::StaticClass())) SetSelectedQuest(SelectedButton);
}

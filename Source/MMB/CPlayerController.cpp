// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "CClimbableRope.h"
#include "CJumpPoints.h"
#include "IPlayerState.h"
#include "IPlayerQuest.h"
#include "CItemDetailUI.h"
#include "CSaveGame.h"
#include "CGameInstance.h"
#include "CESCUI.h"
#include "Blueprint/UserWidget.h"

ACPlayerController::ACPlayerController()
{
	//ConstructorHelpers::FObjectFinder<UUserWidget> WidgetAssetFinder(TEXT("/Game/Player/UI/BP_UI_Player.BP_UI_Player"));
	ConstructorHelpers::FClassFinder<UUserWidget> WidgetAssetFinder(TEXT("/Game/Player/UI/BP_UI_Player"));
	ConstructorHelpers::FClassFinder<UUserWidget> InventoryAssetFinder(TEXT("/Game/Player/UI/BP_UI_Inventory"));
	ConstructorHelpers::FClassFinder<UUserWidget> NPCConversationAssetFinder(TEXT("/Game/Player/UI/BP_NPCConversation"));
	ConstructorHelpers::FClassFinder<UUserWidget> MainUIAssetFinder(TEXT("/Game/Player/UI/BP_Main"));
	ConstructorHelpers::FClassFinder<UUserWidget> AlertAssetFinder(TEXT("/Game/Player/UI/BP_UI_Alert"));
	ConstructorHelpers::FClassFinder<UCDamageUI> DamageAssetFinder(TEXT("/Game/Player/UI/BP_UI_Damage"));
	ConstructorHelpers::FClassFinder<UUserWidget> DroppedItemListAssetFinder(TEXT("/Game/Player/UI/BP_DroppedItemList"));
	ConstructorHelpers::FClassFinder<UCButtonAction> ButtonActionAssetFinder(TEXT("/Game/Player/UI/BP_UI_ButtonAction"));
	ConstructorHelpers::FClassFinder<UCItemDetailUI> ItemDetailAssetFinder(TEXT("/Game/Player/UI/BP_UI_InventoryItem_Detail"));
	ConstructorHelpers::FClassFinder<UCESCUI> ESCAssetFinder(TEXT("/Game/Player/UI/BP_ESC"));


	if (WidgetAssetFinder.Succeeded())			HUDOverlayAsset = WidgetAssetFinder.Class;
	if (InventoryAssetFinder.Succeeded())		ItemInventoryAsset = InventoryAssetFinder.Class;
	if (NPCConversationAssetFinder.Succeeded())	NPCConversationAsset = NPCConversationAssetFinder.Class;
	if (MainUIAssetFinder.Succeeded())			MainUIAsset = MainUIAssetFinder.Class;
	if (AlertAssetFinder.Succeeded())			AlertAsset = AlertAssetFinder.Class;
	if (DamageAssetFinder.Succeeded())			DamageAsset = DamageAssetFinder.Class;
	if (DroppedItemListAssetFinder.Succeeded()) DroppedItemListAsset = DroppedItemListAssetFinder.Class;
	if (ButtonActionAssetFinder.Succeeded())	ButtonActionAsset = ButtonActionAssetFinder.Class;
	if (ItemDetailAssetFinder.Succeeded())		ItemDetailAsset = ItemDetailAssetFinder.Class;
	if (ESCAssetFinder.Succeeded())				ESCMenuAsset = ESCAssetFinder.Class;
}

void ACPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	IIPlayerState* PS = Cast<IIPlayerState>(GetCharacter());
	if (PS == nullptr) return;
	if (PS->GetState(PLAYER_DIED)) HUDOverlay->Tick_DieUIAnim(DeltaTime);
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDOverlayAsset)
	{
		HUDOverlay = Cast<UCUserWidgetPlayerHUD>(CreateWidget<UUserWidget>(this, HUDOverlayAsset));
		if (IsValid(HUDOverlay))
		{
			HUDOverlay->AddToViewport();
			HUDOverlay->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (ItemInventoryAsset)
	{
		ItemInventory = Cast<UCInventory>(CreateWidget<UUserWidget>(GetWorld(), ItemInventoryAsset));
		if (IsValid(ItemInventory))
		{
			ItemInventory->AddToViewport();
			ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (NPCConversationAsset)
	{
		NPCConversation = Cast<UCNPCConversation>(CreateWidget<UUserWidget>(this, NPCConversationAsset));
		if (IsValid(NPCConversation))
		{
			NPCConversation->AddToViewport();
			NPCConversation->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (MainUIAsset)
	{
		MainUI = Cast<UCMainUI>(CreateWidget<UUserWidget>(this, MainUIAsset));
		if (IsValid(MainUI))
		{
			MainUI->AddToViewport();
			MainUI->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (DroppedItemListAsset)
	{
		DroppedItemList = Cast<UCWidgetDroppedItemList>(CreateWidget<UUserWidget>(this, DroppedItemListAsset));
		if (IsValid(DroppedItemList))
		{
			DroppedItemList->AddToViewport();
			DroppedItemList->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *GetWorld()->GetName());
	FString CurrentLevel = GetWorld()->GetName();
	if (CurrentLevel == "MainUILevel")
	{
		HUDOverlay->SetVisibility(ESlateVisibility::Hidden);
		ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		NPCConversation->SetVisibility(ESlateVisibility::Hidden);
		MainUI->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
	}
	else if (CurrentLevel == "TestLevel1" || CurrentLevel == "Startlevel")
	{
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		NPCConversation->SetVisibility(ESlateVisibility::Hidden);
		MainUI->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
	}
	else
	{
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		NPCConversation->SetVisibility(ESlateVisibility::Hidden);
		MainUI->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;

	}
	ESCUI = CreateWidget<UCESCUI>(this, ESCMenuAsset);

	UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());
	if (GI == nullptr) return;
	if (GI->SelectedSaveSlot >= 0) LoadGame(GI->SelectedSaveSlot);
	else LoadGame(GI->TempSaveFileAddress);
}

void ACPlayerController::DequeueDamageUI()
{
	UCDamageUI* D;
	if (DamageUIQueue.Dequeue(D))
	{
		D->RemoveFromViewport();
		D->Destruct();
	}
}

bool ACPlayerController::SetInventoryVisibility()
{
	if (ItemInventory)
	{
		if (ItemInventory->GetVisibility() == ESlateVisibility::Visible)
		{
			ItemInventory->SetVisibility(ESlateVisibility::Hidden);
			bShowMouseCursor = false;
			bEnableClickEvents = false;
			return false;
		}
		else
		{
			ItemInventory->SetVisibility(ESlateVisibility::Visible);
			bShowMouseCursor = true;
			bEnableClickEvents = true;
			return true;
		}
	}
	return false;
}

void ACPlayerController::AddInventoryItem(UClass* ItemClass)
{
	UCInventoryItemData* To = NewObject<UCInventoryItemData>(this, UCInventoryItemData::StaticClass(), FName(FString::FromInt(ItemInventory->ItemList->GetListItems().Num())));
	To->SetstrName(ItemClass->GetName());
	To->SetItemClass(ItemClass);
	ItemInventory->ItemList->AddItem(To);
}

void ACPlayerController::AddInventoryItem(UCInventoryItemData* ItemData)
{
	if (ItemData == nullptr) return;

	if (ItemData->GetItemType() == ITEM_TYPE_GOLD)
	{
		IIPlayerState* PS = Cast<IIPlayerState>(GetCharacter());
		if (PS == nullptr) return;
		PS->GainPlayerGold(ItemData->GetItemCount());
		return;
	}

	for (UObject* HasItem : ItemInventory->ItemList->GetListItems())
	{
		UCInventoryItemData* HasItemData = Cast<UCInventoryItemData>(HasItem);
		if (HasItemData == ItemData)
		{
			HasItemData->SetItemCount(HasItemData->GetItemCount() + ItemData->GetItemCount());
			CheckQuest(ItemData->GetItemClass());
			return;
		}
	}
	ItemInventory->ItemList->AddItem(ItemData);
	CheckQuest(ItemData->GetItemClass());
}

void ACPlayerController::RemoveInventoryItem(UCInventoryItemData* ItemData)
{
	if (ItemData != nullptr) ItemInventory->ItemList->RemoveItem(ItemData);
}

bool ACPlayerController::RemoveEquippedItem(FString EquippedSpace, UCInventoryItemData* ItemData)
{
	if (EquippedSpace == "Weapon")
	{
		ItemInventory->Weapon->RemoveItem(ItemData);
		IIPlayerState* IPlayerState = Cast<IIPlayerState>(GetCharacter());
		IPlayerState->UnEquip();
		return true;
	}
	else if (EquippedSpace == "Artifact")
	{
		ItemInventory->Artifact->RemoveItem(ItemData);
		return true;
	}
	else if (EquippedSpace == "Armor")
	{
		ItemInventory->Armor->RemoveItem(ItemData);
		return true;
	}
	return false;
}

void ACPlayerController::ShowItemDetailUI(UCInventoryItemData* ItemData)
{
	if (ItemData == nullptr) return;

	if (ItemDetailAsset)
	{
		if (ItemDetailUI != nullptr) UnShowItemDetailUI();

		UCItemDetailUI* DetailUI = CreateWidget<UCItemDetailUI>(this, ItemDetailAsset);
		if (IsValid(DetailUI))
		{
			DetailUI->SetDetail(ItemData);

			FVector2D MousePos;
			GetMousePosition(MousePos.X, MousePos.Y);

			DetailUI->SetPositionInViewport(MousePos);
			DetailUI->AddToViewport(1);
			DetailUI->SetVisibility(ESlateVisibility::HitTestInvisible);
			ItemDetailUI = DetailUI;
		}
	}

}

void ACPlayerController::UnShowItemDetailUI()
{
	if (ItemDetailUI == nullptr) return;

	ItemDetailUI->RemoveFromViewport();
	ItemDetailUI->Destruct();
}

bool ACPlayerController::IsOnShop()
{
	return NPCConversation->IsOnShop();
}

//TArray<UObject*> ACPlayerController::GetInventoryItems()
//{
//	return ItemInventory->ItemList->GetListItems();
//}

void ACPlayerController::SetShopInventoryItems(TObjectPtr<class UTileView>& ShopTileList)
{
	ShopTileList->ClearListItems();
	if (ItemInventory->ItemList->GetNumItems() <= 0) return;
	for (UObject* Item : ItemInventory->ItemList->GetListItems())
	{
		ShopTileList->AddItem(Item);
	}
}

void ACPlayerController::ResumeShopInventoryItems()
{
	SetShopInventoryItems(NPCConversation->ItemList_Inventory);
}

void ACPlayerController::SwitchESCMenu()
{
	if (ESCUI == nullptr) return;
	IIPlayerState* PC = Cast<IIPlayerState>(GetCharacter());

	if (!ESCUI->GetIsVisible())
	{
		ESCUI->AddToViewport(1);
		ESCUI->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		if (PC != nullptr) PC->SetState(PLAYER_UI_INTERACTING, true);
	}
	else
	{
		ESCUI->SetVisibility(ESlateVisibility::Hidden);
		ESCUI->RemoveFromViewport();
		bShowMouseCursor = false;
		if (PC != nullptr) PC->SetState(PLAYER_UI_INTERACTING, false);
	}
}

bool ACPlayerController::EquipItem(int ItemType, UCInventoryItemData& ItemData)
{
	if (ItemInventory->EquipItem(ItemType, ItemData))
	{
		RemoveInventoryItem(&ItemData);
		return true;
	}
	return false;
	//ItemInventory->Weapon->AddItem(&ItemData);
	//RemoveInventoryItem(&ItemData);
	//return true;
	//switch (ItemType)
	//{
	//case(ITEM_TYPE_WEAPON):
	//	ItemInventory->Weapon->AddItem(&ItemData);
	//	RemoveInventoryItem(&ItemData);
	//	return true;
	//case(ITEM_TYPE_ARTIFACT):
	//	ItemInventory->Artifact->AddItem(&ItemData);
	//	RemoveInventoryItem(&ItemData);
	//	return true;
	//case(ITEM_TYPE_ARMOR):
	//	ItemInventory->Armor->AddItem(&ItemData);
	//	RemoveInventoryItem(&ItemData);
	//	return true;
	//default:
	//	return false;
	//}
}

void ACPlayerController::SetPressedButton(UUserWidget* SelectedButton)
{
	NPCConversation->SetSelectedButton(SelectedButton);
}

void ACPlayerController::SetNPCConversationVisibility(bool e, ACStaticNPC* npc)
{
	//UE_LOG(LogTemp, Log, TEXT("NPC Conversation UI Set %s"), (e ? TEXT("True") : TEXT("False")));

	if (e)
	{
		TArray<FNPCDialoguesRow*> DialogueRow = npc->GetDialogue();

		//NPCConversation->SetNPCName(FText::FromString(FString(TEXT("Molu"))));
		NPCConversation->SetNPC(npc);
		if (npc != nullptr)
		{
			if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetPawn()))
			{
				SetViewTargetWithBlend(npc->SetCameraOn(true, PC->CameraComponent->GetComponentTransform()));
			}
		}

		if (DialogueRow.Num() > 0)
		{
			NPCConversation->SetDialogues(DialogueRow);
			//NPCConversation->SetNPCName(DialogueRow->NPCName);
			//NPCConversation->SetNPCLine(DialogueRow->NPCDialogue);
		}

		NPCConversation->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		bEnableClickEvents = true;
	}
	else
	{
		NPCConversation->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
		bEnableClickEvents = false;

		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetPawn()))
		{
			if (npc != nullptr)
			{
				npc->SetCameraOn(false, PC->CameraComponent->GetComponentTransform());
			}
			SetViewTargetWithBlend(PC->CameraComponent->GetOwner());
		}
	}
}

void ACPlayerController::ResetNPCConversation(ACStaticNPC* npc)
{
	//NPCConversation->SetItemList(npc, );
}

void ACPlayerController::AddAlert(FText e)
{
	if (AlertAsset)
	{
		AlertUI = Cast<UCAlert>(CreateWidget<UUserWidget>(this, AlertAsset));
		if (IsValid(AlertUI))
		{
			AlertUI->AddToViewport();
			AlertUI->SetVisibility(ESlateVisibility::Visible);
			AlertUI->SetAlertMessage(e);
		}
	}
}

void ACPlayerController::ShowDamageUI(float Damage, FVector Location, FColor C, bool IsAttacked)
{
	if (DamageAsset)
	{
		UCDamageUI* DamageUI = CreateWidget<UCDamageUI>(this, DamageAsset);
		if (IsValid(DamageUI))
		{
			FWidgetTransform Transform = FWidgetTransform();
			FVector2D ScreenLocation;
			if (IsAttacked)
			{
				int32 X;
				int32 Y;
				GetViewportSize(X, Y);
				ScreenLocation = FVector2D(X / 2, Y / 2);
			}
			else ProjectWorldLocationToScreen(Location, ScreenLocation);

			DamageUI->SetPositionInViewport(ScreenLocation);
			UE_LOG(LogTemp, Log, TEXT("Screen Location : %s"), *ScreenLocation.ToString());
			Transform.Translation = ScreenLocation;

			//if (ProjectWorldLocationToScreen(Location, ScreenLocation))
			//{
			//	DamageUI->SetPositionInViewport(ScreenLocation);
			//	UE_LOG(LogTemp, Log, TEXT("Screen Location : %s"), *ScreenLocation.ToString());
			//	Transform.Translation = ScreenLocation;
			//}
			DamageUI->SetDamage(Damage);
			DamageUI->SetDamageColor(C);
			DamageUI->AddToViewport();
			DamageUI->SetVisibility(ESlateVisibility::Visible);
			DamageUIQueue.Enqueue(DamageUI);
			GetWorld()->GetTimerManager().SetTimer(DamageShowTimer, this, &ACPlayerController::DequeueDamageUI, 1.f);
		}
	}
}

void ACPlayerController::AlertSwingby(float e, FText Line)
{
	NPCConversation->AlertSwingby(e, Line);
}

void ACPlayerController::AddQuest(FQuestsRow* Q)
{
	FString QN = Q->QuestName;
	UCQuestData* QuestData = NewObject<UCQuestData>(this, UCQuestData::StaticClass(), FName(QN));
	QuestData->SetDetails(Q);
	HUDOverlay->QuestList->AddItem(QuestData);

	// If With Initializer
	int QuestInitializer = QuestData->GetQuestInitializeIndex();
	if (QuestInitializer < 0) return;
	IIPlayerQuest* QuestManage = Cast<IIPlayerQuest>(GetCharacter());
	if (QuestManage == nullptr) return;
	QuestManage->QuestInitialize(QuestInitializer);

	//UE_LOG(LogTemp, Log, TEXT("PLAYER CONTROLLER :: Adding Quest %s"), *QuestData->GetQuestName());
}

void ACPlayerController::AddQuest(UCQuestData* QuestData)
{
	HUDOverlay->QuestList->AddItem(QuestData);

	// If With Initializer
	int QuestInitializer = QuestData->GetQuestInitializeIndex();
	if (QuestInitializer < 0) return;
	IIPlayerQuest* QuestManage = Cast<IIPlayerQuest>(GetCharacter());
	if (QuestManage == nullptr) return;
	QuestManage->QuestInitialize(QuestInitializer);
}

void ACPlayerController::CheckQuest(UObject* ToCheckObject)
{
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		UCQuest* WQ = Cast<UCQuest>(QuestWidget);
		if (WQ == nullptr) continue;
		if (WQ->IsCleared()) continue;
		if (WQ->RefreshQuestRecap(ToCheckObject))
		{
			IIPlayerQuest* QuestManage = Cast<IIPlayerQuest>(GetCharacter());
			if (QuestManage == nullptr) continue;
			QuestManage->QuestClear(WQ->GetQuestRewardIndex());
		}
	}
	HUDOverlay->QuestList->RequestRefresh();
}

void ACPlayerController::CheckQuest(UClass* ToCheckObjectClass)
{
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		UCQuest* WQ = Cast<UCQuest>(QuestWidget);
		if (WQ == nullptr) continue;
		if (WQ->IsCleared()) continue;
		if (WQ->RefreshQuestRecap(ToCheckObjectClass))
		{
			IIPlayerQuest* QuestManage = Cast<IIPlayerQuest>(GetCharacter());
			if (QuestManage == nullptr) continue;
			QuestManage->QuestClear(WQ->GetQuestRewardIndex());
		}
	}
	HUDOverlay->QuestList->RequestRefresh();
}

bool ACPlayerController::CheckQuest_Cleared(FString QuestName)
{
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		if (UCQuest* WQ = Cast<UCQuest>(QuestWidget))
		{
			if (QuestName == WQ->GetQuestName() && WQ->IsCleared())
			{
				return true;
			}
		}
	}
	//UE_LOG(LogTemp, Log, TEXT("Quest Check Failed"));
	return false;
}

void ACPlayerController::ShowDroppedItemList(bool e, ACDroppedItem& Dropped, UCInventoryItemData* ItemData)
{
	if (DroppedItemList == nullptr) return;
	if (e)
	{
		DroppedItemList->SetVisibility(ESlateVisibility::Visible);
		DroppedItemList->ItemList->AddItem(ItemData);
		//if (Dropped == nullptr) return;
		DroppedItemPtrArr.Add(&Dropped);
		PickUpItemInteract_ShowAndInputReady();
	}
	else
	{
		DroppedItemList->ItemList->RemoveItem(ItemData);
		if (DroppedItemPtrArr.Contains(&Dropped)) DroppedItemPtrArr.Remove(&Dropped);
		if (DroppedItemList->ItemList->GetNumItems() == 0)
		{
			DroppedItemList->SetVisibility(ESlateVisibility::Hidden);
			DroppedItemPtrArr.Empty();
			NPCInteract_UnShow();
		}
	}
}

void ACPlayerController::OnInteract()
{
	if (ButtonActionUI == nullptr) return;
	switch(ButtonActionUI->GetButtonMode())
	{
	case(INTERACT_BUTTON_MODE_NPCDIALOGUE):
		NPCInteract_Interact();
		return;
	case(INTERACT_BUTTON_MODE_CLIMBROPE):
		ClimbRopeInteract_Interact();
		return;
	case(INTERACT_BUTTON_MODE_JUMPPOINTS):
		JumpPointsInteract_Interact();
		return;
	case(INTERACT_BUTTON_MODE_PICKUPITEM):
		PickUpItemInteract_Interact();
		return;
	}
}

void ACPlayerController::NPCInteract_ShowAndInputReady(ACStaticNPC* NPC)
{
	if (ButtonActionUI != nullptr) NPCInteract_UnShow();
	ButtonActionUI = CreateWidget<UCButtonAction>(this, ButtonActionAsset);
	if (IsValid(ButtonActionUI))
	{
		FVector MiddlePos = (GetCharacter()->GetActorLocation() + (GetCharacter()->GetActorRightVector() * 100.f + GetCharacter()->GetActorUpVector() * 100.f));
		FVector2D ScreenLocation;
		ProjectWorldLocationToScreen(MiddlePos, ScreenLocation);

		ButtonActionUI->AddToViewport();
		ButtonActionUI->SetButtonMode(INTERACT_BUTTON_MODE_NPCDIALOGUE);
		ButtonActionUI->SetNPC(NPC);
		ButtonActionUI->SetPositionInViewport(ScreenLocation);
	}
}

void ACPlayerController::NPCInteract_Interact()
{
	if (ButtonActionUI == nullptr) return;
	//bool flag = false;
	//TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	//for (UUserWidget* QuestWidget : QuestWidgets)
	//{
	//	UCQuest* WQ = Cast<UCQuest>(QuestWidget);
	//	if (WQ == nullptr) continue;
	//	if (WQ->IsCleared() && WQ->GetGivenNPC() == ButtonActionUI->GetNPC())
	//	{
	//		flag = true;
	//		IIPlayerQuest* QuestManage = Cast<IIPlayerQuest>(GetCharacter());
	//		if (QuestManage == nullptr) continue;
	//		QuestManage->QuestClear(WQ->GetQuestRewardIndex());
	//		HUDOverlay->QuestList->RemoveItem(WQ->GetListItem());
	//		WQ->Destruct();

	//		UE_LOG(LogTemp, Log, TEXT("Quest Reward"));

	//		// TO DO
	//		// Data Table =+ Reward Dialogue Post Line
	//		// PostLine -> Reward() Bind
	//		//
	//	}
	//}
	//HUDOverlay->QuestList->RequestRefresh();
	//if (flag) return;

	SetNPCConversationVisibility(true, ButtonActionUI->GetNPC());
	NPCInteract_UnShow();
}

void ACPlayerController::NPCInteract_UnShow()
{
	if (ButtonActionUI == nullptr) return;
	ButtonActionUI->RemoveFromViewport();
	ButtonActionUI = nullptr;
}

void ACPlayerController::ClimbRopeInteract_ShowAndInputReady(ACClimbableRope* Rope)
{
	if (ButtonActionUI != nullptr) NPCInteract_UnShow();
	ButtonActionUI = CreateWidget<UCButtonAction>(this, ButtonActionAsset);
	if (IsValid(ButtonActionUI))
	{
		FVector MiddlePos = (GetCharacter()->GetActorLocation() + (GetCharacter()->GetActorRightVector() * 100.f + GetCharacter()->GetActorUpVector() * 100.f));
		FVector2D ScreenLocation;
		ProjectWorldLocationToScreen(MiddlePos, ScreenLocation);

		ButtonActionUI->AddToViewport();
		ButtonActionUI->SetButtonMode(INTERACT_BUTTON_MODE_CLIMBROPE);
		ButtonActionUI->SetRope(Rope);
		ButtonActionUI->SetPositionInViewport(ScreenLocation);
	}
}

void ACPlayerController::ClimbRopeInteract_Interact()
{
	if (ButtonActionUI == nullptr) return;
	GraspingRope = ButtonActionUI->GetRope();
	if (GraspingRope == nullptr) return;
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetPawn());
	if (PC == nullptr) return;
	NPCInteract_UnShow();

	//PC->OnGraspRope(GraspingRope->GetIsUpWard() ? GraspingRope->GetDownLocation() : GraspingRope->GetUpLocation());
	PC->OnGraspRope(GraspingRope->GetIsUpWard() ? GraspingRope->GetDownTransform() : GraspingRope->GetUpTransform());
	//UE_LOG(LogTemp, Log, TEXT("Player Contoller : Player Climbing State Set True"));
}

void ACPlayerController::ClimbRopeInteract_Move(FVector& NextTickClimbPos, bool& Result, bool IsUpWard)
{
	if (GraspingRope == nullptr) return;
	if (IsUpWard) GraspingRope->ClimbUp(NextTickClimbPos, Result);
	else GraspingRope->ClimbDown(NextTickClimbPos, Result);
}

void ACPlayerController::JumpPointsInteract_ShowAndInputReady(ACJumpPoints* Jumppoints, int JumpPoint)
{
	if (ButtonActionUI != nullptr) NPCInteract_UnShow();
	ButtonActionUI = CreateWidget<UCButtonAction>(this, ButtonActionAsset);
	if (IsValid(ButtonActionUI))
	{
		FVector MiddlePos = (GetCharacter()->GetActorLocation() + (GetCharacter()->GetActorRightVector() * 100.f + GetCharacter()->GetActorUpVector() * 100.f));
		FVector2D ScreenLocation;
		ProjectWorldLocationToScreen(MiddlePos, ScreenLocation);

		ButtonActionUI->AddToViewport();
		ButtonActionUI->SetButtonMode(INTERACT_BUTTON_MODE_JUMPPOINTS);
		ButtonActionUI->SetJumpPoints(Jumppoints);
		ButtonActionUI->SetPositionInViewport(ScreenLocation);
		JumpStartPoint = JumpPoint;
	}
}

void ACPlayerController::JumpPointsInteract_Interact()
{
	if (ButtonActionUI == nullptr) return;
	ACJumpPoints* JumpPoints = ButtonActionUI->GetJumpPoints();
	if (JumpPoints == nullptr) return;
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetPawn());
	if (PC == nullptr) return;
	JumpPoints->TransferCharacter(PC, JumpStartPoint);
	NPCInteract_UnShow();
	//PC->GetCharacterMovement()->GravityScale = 0;
	//PC->GetMovementComponent()->StopMovementImmediately();
	//PC->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
}

void ACPlayerController::PickUpItemInteract_ShowAndInputReady()
{
	if (ButtonActionUI != nullptr) NPCInteract_UnShow();
	ButtonActionUI = CreateWidget<UCButtonAction>(this, ButtonActionAsset);
	if (IsValid(ButtonActionUI))
	{
		FVector MiddlePos = (GetCharacter()->GetActorLocation() + (GetCharacter()->GetActorRightVector() * -100.f + GetCharacter()->GetActorUpVector() * 100.f));
		FVector2D ScreenLocation;
		ProjectWorldLocationToScreen(MiddlePos, ScreenLocation);

		ButtonActionUI->AddToViewport();
		ButtonActionUI->SetButtonMode(INTERACT_BUTTON_MODE_PICKUPITEM);
		ButtonActionUI->SetPositionInViewport(ScreenLocation);
		//ButtonActionUI->
	}
}

void ACPlayerController::PickUpItemInteract_Interact()
{
	if (ButtonActionUI == nullptr) return;
	TArray<UObject*> tempArr = DroppedItemList->ItemList->GetListItems();
	UCInventoryItemData* tempItem;
	ACDroppedItem* tempDroppedItem;
	for (auto& temp : tempArr)
	{
		tempItem = Cast<UCInventoryItemData>(temp);
		if (tempItem == nullptr) continue;
		AddInventoryItem(tempItem);
		//UE_LOG(LogTemp, Log, TEXT("PickUpItem : %s"), *tempItem->GetstrName())
	}
	for (auto& temp : DroppedItemPtrArr)
	{
		tempDroppedItem = Cast<ACDroppedItem>(temp);
		if (tempDroppedItem == nullptr) continue;
		tempDroppedItem->Destroy();
	}
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetCharacter());
	if (PC == nullptr) return;
	PC->PickUp.ExecuteIfBound();
	NPCInteract_UnShow();
}

void ACPlayerController::CharacterDied(bool b)
{
	HUDOverlay->ShowDieUI(b);
}

void ACPlayerController::SetSelectedPortal(int ArrIndex)
{
	if (NPCConversation == nullptr) return;
	NPCConversation->SetLoadedMapIndex(ArrIndex);
}

UINT32 ACPlayerController::IsPossesQuestCleared(FString QuestName)
{
	//bool Flag_Match = false;
	//bool Flag_Cleared = false;
	//bool Flag_AleardyCleared = false; // TODO

	//for (UCQuest* ClearedQuest : ClearedQuestArr)
	for (FString ClearedQuest : ClearedQuestArr)
	{
		//if (ClearedQuest->GetQuestName() == QuestName) return QUEST_ALEARDY_CLEARED;
		if (ClearedQuest == QuestName) return QUEST_ALEARDY_CLEARED;
	}

	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		UCQuest* WQ = Cast<UCQuest>(QuestWidget);
		if (WQ == nullptr) continue;

		if (WQ->GetQuestName() == QuestName)
		{
			//Flag_Match = true;
			if (WQ->IsCleared()) return QUEST_CLEARED; //Flag_Cleared = true;
			return QUEST_ALREADY_HAVE;
		}
	}
	return QUEST_NO_MATCH;
	//if (!Flag_Match) return QUEST_NO_MATCH;
	//if (!Flag_Cleared) return QUEST_ALREADY_HAVE;
	//return QUEST_CLEARED;
	//return QUEST_ALEARDY_CLEARED; TODO
}

void ACPlayerController::MoveQuestToClearedByQuestName(FString QuestName)
{
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	UCQuest* ClearedQuest = nullptr;
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		UCQuest* WQ = Cast<UCQuest>(QuestWidget);
		if (WQ == nullptr) continue;

		if (WQ->GetQuestName() == QuestName)
		{
			ClearedQuest = WQ;
			break;
		}
	}
	if (ClearedQuest == nullptr) return;
	
	HUDOverlay->QuestList->RemoveItem(ClearedQuest->GetListItem());
	ClearedQuestArr.Add(ClearedQuest->GetQuestName());
}

void ACPlayerController::RemoveQuest(UObject* QuestDat)
{
	if (HUDOverlay == nullptr) return;
	HUDOverlay->QuestList->RemoveItem(QuestDat);
}

bool ACPlayerController::IsQualifiedQuest(TArray<FString> RequiredQuestsArr)
{
	bool Flag = false;
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (FString RequiredQuest : RequiredQuestsArr)
	{
		//for (UCQuest* QuestWidget : ClearedQuestArr)
		for (FString QuestWidget : ClearedQuestArr)
		{
			//if (QuestWidget->GetQuestName() == RequiredQuest)
			if (QuestWidget == RequiredQuest)
			{
				Flag = true;
				break;
			}
		}
		if (!Flag) return false;
		Flag = false;
	}
	return true;
}

void ACPlayerController::SaveGame(int32 SlotIndex)
{
	UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	if (SaveGameInstance != nullptr)
	{
		SaveGameInstance->SaveSlotName = "Save" + FString::FromInt(SlotIndex);
		SaveGameInstance->SaveIndex = SlotIndex;

		TArray<FName> ItemRowNames;
		TArray<int> ItemCounts;
		for (UObject* Item : ItemInventory->ItemList->GetListItems())
		{
			UCInventoryItemData* ID = Cast<UCInventoryItemData>(Item);
			if (ID != nullptr)
			{
				SaveGameInstance->SavedItemListQ.Add(ID->GetItemCount());
				SaveGameInstance->SavedItemList.Add(ID->GetDT_RowName());
			}
		}
		if (UCInventoryItemData* W = Cast<UCInventoryItemData>(ItemInventory->Weapon->GetItemAt(0)))
		{
			SaveGameInstance->SavedWeapon = W->GetDT_RowName();
		}
		if (UCInventoryItemData* A = Cast<UCInventoryItemData>(ItemInventory->Artifact->GetItemAt(0)))
		{
			SaveGameInstance->SavedArtifact = A->GetDT_RowName();
		}
		if (UCInventoryItemData* M = Cast<UCInventoryItemData>(ItemInventory->Armor->GetItemAt(0)))
		{
			SaveGameInstance->SavedArmor = M->GetDT_RowName();
		}

		IIPlayerState* PC = Cast<IIPlayerState>(GetCharacter());
		if (PC != nullptr)
		{
			SaveGameInstance->SavedGold = PC->GetPlayerGold();
		}
		SaveGameInstance->SavedLevel = GetWorld()->GetCurrentLevel()->GetPathName();
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
}

void ACPlayerController::SaveGame(TArray<uint8>& MemoryAddress)
{
	UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	if (SaveGameInstance != nullptr)
	{
		SaveGameInstance->SaveSlotName = "Save" + FString::FromInt(-1);
		SaveGameInstance->SaveIndex = -1;

		TArray<FName> ItemRowNames;
		TArray<int> ItemCounts;
		for (UObject* Item : ItemInventory->ItemList->GetListItems())
		{
			UCInventoryItemData* ID = Cast<UCInventoryItemData>(Item);
			if (ID != nullptr)
			{
				SaveGameInstance->SavedItemListQ.Add(ID->GetItemCount());
				SaveGameInstance->SavedItemList.Add(ID->GetDT_RowName());
			}
		}
		if (UCInventoryItemData* W = Cast<UCInventoryItemData>(ItemInventory->Weapon->GetItemAt(0)))
		{
			SaveGameInstance->SavedWeapon = W->GetDT_RowName();
		}
		if (UCInventoryItemData* A = Cast<UCInventoryItemData>(ItemInventory->Artifact->GetItemAt(0)))
		{
			SaveGameInstance->SavedArtifact = A->GetDT_RowName();
		}
		if (UCInventoryItemData* M = Cast<UCInventoryItemData>(ItemInventory->Armor->GetItemAt(0)))
		{
			SaveGameInstance->SavedArmor = M->GetDT_RowName();
		}

		IIPlayerState* PC = Cast<IIPlayerState>(GetCharacter());
		if (PC != nullptr)
		{
			SaveGameInstance->SavedGold = PC->GetPlayerGold();
		}
		SaveGameInstance->SavedLevel = GetWorld()->GetCurrentLevel()->GetPathName();
	}
	//UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
	UGameplayStatics::SaveGameToMemory(SaveGameInstance, MemoryAddress);
}

void ACPlayerController::LoadGame(int32 SaveSlot)
{
	if (SaveSlot < 0) return;
	UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Save" + FString::FromInt(SaveSlot), SaveSlot));
	AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (SaveGameInstance == nullptr || GM == nullptr) return;

	for (int i = 0; i < SaveGameInstance->SavedItemList.Num(); i++)
	{
		UCInventoryItemData* ID = GM->GetItem(SaveGameInstance->SavedItemList[i], SaveGameInstance->SavedItemListQ[i]);
		if (ID == nullptr) continue;
		AddInventoryItem(ID);
	}

	IIPlayerState* PC = Cast<IIPlayerState>(GetCharacter());
	if (PC == nullptr) return;

	UCInventoryItemData* W = GM->GetItem(SaveGameInstance->SavedWeapon);
	if (W)
	{
		AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(W->GetItemClass(), GetCharacter()->GetActorLocation(), FRotator::ZeroRotator);
		IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor);
		if (isWeapon != nullptr)
		{
			isWeapon->SetIsEquiped(true);
			isWeapon->SetWeaponName(FName(W->GetstrName()));
			isWeapon->SetAttackDamage(W->GetAttackDamage());

			PC->Equip(*spawnedActor);
		}
		EquipItem(ITEM_TYPE_WEAPON, *W);
	}

	UCInventoryItemData* M = GM->GetItem(SaveGameInstance->SavedArmor);
	if (M) EquipItem(ITEM_TYPE_ARMOR, *M);
	UCInventoryItemData* A = GM->GetItem(SaveGameInstance->SavedArtifact);
	if (A) EquipItem(ITEM_TYPE_ARTIFACT, *A);

	PC->SetPlayerGold(SaveGameInstance->SavedGold);
}

void ACPlayerController::LoadGame(TArray<uint8> MemoryAddress)
{
	UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromMemory(MemoryAddress));
	AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (SaveGameInstance == nullptr || GM == nullptr) return;

	for (int i = 0; i < SaveGameInstance->SavedItemList.Num(); i++)
	{
		UCInventoryItemData* ID = GM->GetItem(SaveGameInstance->SavedItemList[i], SaveGameInstance->SavedItemListQ[i]);
		if (ID == nullptr) continue;
		AddInventoryItem(ID);
	}

	IIPlayerState* PC = Cast<IIPlayerState>(GetCharacter());
	if (PC == nullptr) return;

	UCInventoryItemData* W = GM->GetItem(SaveGameInstance->SavedWeapon);
	if (W)
	{
		AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(W->GetItemClass(), GetCharacter()->GetActorLocation(), FRotator::ZeroRotator);
		IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor);
		if (isWeapon != nullptr)
		{
			isWeapon->SetIsEquiped(true);
			isWeapon->SetWeaponName(FName(W->GetstrName()));
			isWeapon->SetAttackDamage(W->GetAttackDamage());

			PC->Equip(*spawnedActor);
		}
		EquipItem(ITEM_TYPE_WEAPON, *W);
	}

	UCInventoryItemData* M = GM->GetItem(SaveGameInstance->SavedArmor);
	if (M) EquipItem(ITEM_TYPE_ARMOR, *M);
	UCInventoryItemData* A = GM->GetItem(SaveGameInstance->SavedArtifact);
	if (A) EquipItem(ITEM_TYPE_ARTIFACT, *A);

	PC->SetPlayerGold(SaveGameInstance->SavedGold);
}

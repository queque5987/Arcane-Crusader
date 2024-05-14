// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "CClimbableRope.h"
#include "CJumpPoints.h"
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


	if (WidgetAssetFinder.Succeeded())			HUDOverlayAsset = WidgetAssetFinder.Class;
	if (InventoryAssetFinder.Succeeded())		ItemInventoryAsset = InventoryAssetFinder.Class;
	if (NPCConversationAssetFinder.Succeeded())	NPCConversationAsset = NPCConversationAssetFinder.Class;
	if (MainUIAssetFinder.Succeeded())			MainUIAsset = MainUIAssetFinder.Class;
	if (AlertAssetFinder.Succeeded())			AlertAsset = AlertAssetFinder.Class;
	if (DamageAssetFinder.Succeeded())			DamageAsset = DamageAssetFinder.Class;
	if (DroppedItemListAssetFinder.Succeeded()) DroppedItemListAsset = DroppedItemListAssetFinder.Class;
	if (ButtonActionAssetFinder.Succeeded())	ButtonActionAsset = ButtonActionAssetFinder.Class;
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
	else if (CurrentLevel == "TestLevel1")
	{
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		ItemInventory->SetVisibility(ESlateVisibility::Hidden);
		NPCConversation->SetVisibility(ESlateVisibility::Hidden);
		MainUI->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
	}
}

void ACPlayerController::DequeueDamageUI()
{
	UCDamageUI* D;
	if (DamageUIQueue.Dequeue(D))
	{
		D->RemoveFromViewport();
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
	if (ItemData != nullptr) ItemInventory->ItemList->AddItem(ItemData);
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
	int QT = Q->QuestType;
	FString QN = Q->QuestName;
	UCQuestData* QuestData = NewObject<UCQuestData>(this, UCQuestData::StaticClass(), "Quest0");
	QuestData->SetDetails(Q);
	HUDOverlay->QuestList->AddItem(QuestData);

	UE_LOG(LogTemp, Log, TEXT("PLAYER CONTROLLER :: Adding Quest %s"), *QuestData->GetQuestName());
}

void ACPlayerController::CheckQuest(UClass* ToCheckClass)
{
	//TArray<UObject*> Quests = HUDOverlay->QuestList->GetListItems();
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		if (UCQuest* WQ = Cast<UCQuest>(QuestWidget))
		{
			WQ->RefreshQuestRecap(ToCheckClass);
		}
	}
	HUDOverlay->QuestList->RequestRefresh();
}

bool ACPlayerController::CheckQuest_Cleared(FString QuestName)
{
	//TArray<UObject*> Quests = HUDOverlay->QuestList->GetListItems();
	UE_LOG(LogTemp, Log, TEXT("Checking Quest Name : %s"), *QuestName);
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
	UE_LOG(LogTemp, Log, TEXT("Quest Check Failed"));
	return false;
}

void ACPlayerController::ShowDroppedItemList(bool e, ACDroppedItem* Dropped, UCInventoryItemData* ItemData)
{
	if (e)
	{
		DroppedItemList->SetVisibility(ESlateVisibility::Visible);
		DroppedItemList->ItemList->AddItem(ItemData);
	}
	else
	{
		DroppedItemList->ItemList->RemoveItem(ItemData);
		if (DroppedItemList->ItemList->GetNumItems() == 0) DroppedItemList->SetVisibility(ESlateVisibility::Hidden);
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

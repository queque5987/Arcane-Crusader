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
//#include "Quest_HuntMonster.h"
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

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	TArray<class UCAlert*> AlertUIList;
	FTimerHandle DamageShowTimer;
	TQueue<class UCDamageUI*> DamageUIQueue;

	TArray<class ACDroppedItem*> DroppedItemPtrArr;

	class UCButtonAction* ButtonActionUI;
	class ACClimbableRope* GraspingRope;
	int32 JumpStartPoint;
	UFUNCTION()
	void DequeueDamageUI();
public:
	bool SetInventoryVisibility();
	void AddInventoryItem(UClass* ItemClass);
	void AddInventoryItem(class UCInventoryItemData* ItemData);
	void SetNPCConversationVisibility(bool e, class ACStaticNPC* npc = nullptr);
	void ResetNPCConversation(class ACStaticNPC* npc);
	void AddAlert(FText e);
	void ShowDamageUI(float Damage, FVector Location, FColor C = FColor::White, bool IsAttacked = false);
	void AlertSwingby(float e, FText Line);
	void AddQuest(struct FQuestsRow* Q);
	void CheckQuest(class ACPlayerCharacter* PC, UObject* ToCheckObject);
	bool CheckQuest_Cleared(FString QuestName);
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
};

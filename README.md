![image](https://github.com/user-attachments/assets/3f7a4083-a1c2-49d1-aa4a-68e36d18874e)

# Arcane Crusader<br><br>플레이 영상

[![플레이 영상](https://img.youtube.com/vi/-hKQ6otIoGA/0.jpg)](https://youtu.be/-hKQ6otIoGA)<br><br>

# 0. 목차
- [1. UI]()
  
	* [**1-1. 인벤토리 시스템**](#1-1-인벤토리-시스템)
	    + [*1-1-1. 아이템 획득*](#1-1-1-아이템-획득)
	    + [*1-1-2. 아이템 세부정보*](#1-1-2-아이템-세부정보)

	![ui_inventory-supp](https://github.com/user-attachments/assets/db793861-1f2b-4a1a-8cfa-2ec56a575776)

	* [**1-2. NPC 상호작용 시스템**](#1-2-NPC-상호작용-시스템)
	    + [*1-2-1. NPC 대화 진행*](#1-2-1-npc-대화-진행)
	    + [*1-2-2. NPC 시점 변환*](#1-2-2-npc-시점-변환)

	* [**1-3. 상점 시스템**](#1-3-상점-시스템)
	    + [*1-3-1. 상점 아이템 위젯*](#1-3-1-상점-아이템-위젯)
	    + [*1-3-2. 상점 구매 / 판매*](#1-3-2-상점-구매-판매)
   
 	![ui_shop2_supp](https://github.com/user-attachments/assets/ac0f9d4d-11b1-4d6a-bbee-636b49239d90)

	* [**1-4. 퀘스트 시스템**](#1-4-퀘스트-시스템)
	    + [*1-4-1. 퀘스트 수락*](#1-4-1-퀘스트-수락)
	    + [*1-4-2. 퀘스트 완료*](#1-4-2-퀘스트-완료)
  
	![ui_quest_supp](https://github.com/user-attachments/assets/5446f413-2611-4100-878b-a2c84d26580e)

	* [**1-5. 스테이지 선택 시스템**](#1-5-스테이지-선택-시스템)
	    + [*1-5-1. 스테이지 선택 UI*](#1-5-1-스테이지-선택-UI)
  
 	![ui_teleport_supp](https://github.com/user-attachments/assets/9b01dfc6-941f-4185-bea1-e1e859be84f6)

	* [**1-6. 저장 시스템**](#1-6-저장-시스템)
	    + [*1-6-1. 메인 화면 UI*](#1-6-1-메인-화면-UI)
  
	![main_supp](https://github.com/user-attachments/assets/2f56297a-2704-4731-86a4-9053e34a6743)

	* [**HUD 시스템**]()
 
	![ui_whole_supp](https://github.com/user-attachments/assets/c4aae09e-9d13-4bdc-a5f9-0f5b09719a6e)

- [2. 전투]()
	* [**플레이어 State 관리**]()
	* [**회피 시스템**]()

	![atk_bs_evade_supp](https://github.com/user-attachments/assets/0d77c391-1872-4684-a1a7-b81bbf546fa4)

	* [**대미지 표기 시스템**]()
	* [**아이템 드랍 시스템**]()

	![atk_rs_ult_supp](https://github.com/user-attachments/assets/61a85212-024a-4f96-97ef-d01e9b9b1dd4)

	* [**연속 공격 시스템**]()

	![atk_bs_pyeong](https://github.com/user-attachments/assets/08135222-e660-438f-90cf-a55e458e2e13)
	![atk_bs_switch](https://github.com/user-attachments/assets/6d5263ff-2c25-4d35-bf89-acbef3ae8f13)

	* [**이펙트 소환 최적화 시스템**]()
	* [**투사체 공격 시스템**]()

	![atk_rs_switch_supp](https://github.com/user-attachments/assets/dc910141-aad5-41e4-bbdb-d599f067f2dc)
------
# 1. UI
## 1-1. 인벤토리 시스템

![ui_inventory](https://github.com/user-attachments/assets/b213e1b4-996f-4733-8237-d51efaa40836)

인벤토리는 장비탭과 소지탭을 구분하여 구현하였습니다.

소비 아이템의 경우 클릭하여 퀵슬롯에 아이템을 등록할 수 있도록 구현하였습니다.

```C++
class MMB_API UCInventory : public UUserWidget
{
	GENERATED_BODY()
	
	UCInventory(const FObjectInitializer& ObjectInitializer);
	
	public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> ItemList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerGold;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Weapon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Artifact;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> Armor;
	
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	
	bool EquipItem(int ItemType, class UCInventoryItemData& ToEquipItemData);
};
```

TileView를 사용하여 장착 아이템과 소지 아이템이 저장될 공간을 구분하였습니다.

### 1-1-1. 아이템 획득
```C++
void ACPlayerController::AddInventoryItem(UCInventoryItemData* ItemData, bool OnPickup)
{
	if (ItemData == nullptr) return;
	
	if (ItemData->GetItemType() == ITEM_TYPE_GOLD)
	{
		IIPlayerState* PS = Cast<IIPlayerState>(GetCharacter());
		if (PS == nullptr) return;
		PS->GainPlayerGold(ItemData->GetItemCount());
		return;
	}
	
	if (ItemData->GetItemType() > 3)
	{
		for (UObject* HasItem : ItemInventory->ItemList->GetListItems())
		{
			if (HasItem == nullptr) continue;
			UCInventoryItemData* HasItemData = Cast<UCInventoryItemData>(HasItem);
			if (HasItemData->GetstrName() == ItemData->GetstrName())
			{
				HasItemData->SetItemCount(
					HasItemData->GetItemCount() + ItemData->GetItemCount());
				CheckQuest(ItemData->GetItemClass());
				return;
			}
		}
	}
	ItemInventory->ItemList->AddItem(ItemData);
	CheckQuest(ItemData->GetItemClass());
}
```
아이템 습득 시, CInventoryItemData 객체를 ItemList에 저장합니다.

중첩이 가능한 아이템일 경우, 대신 아이템의 카운트를 증가시킵니다.

```C++
void ACPlayerController::CheckQuest(UClass* ToCheckObjectClass, int AchievedActionType)
{
	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		UCQuest* WQ = Cast<UCQuest>(QuestWidget);
		if (WQ == nullptr) continue;
		if (WQ->IsCleared()) continue;
		if (WQ->RefreshQuestRecap(ToCheckObjectClass, AchievedActionType)) // If Cleared Quest (Required Class All Completed)
		{
			IIPlayerQuest* QuestManage = Cast<IIPlayerQuest>(GetCharacter());
			if (QuestManage == nullptr) continue;
			QuestManage->QuestClear(WQ->GetQuestRewardIndex());
		}
	}
	HUDOverlay->QuestList->RequestRefresh();
}
```
아이템 습득 처리 이후, CheckQuest 함수를 호출하여 퀘스트 달성 여부를 검사합니다.

플레이어가 가지고 있는 퀘스트 위젯을 전부 순회하며 RefreshQuestRecap 함수를 통해 퀘스트가 가지고 있는 목표와 일치하는지 검사합니다.

```C++
bool UCQuest::RefreshQuestRecap(UClass* AchievedObjectClass, int AchievedActionType)
{
	FString Recap = QuestRecapString + "\n";
	int Achieved = RequiredClasses.Num();
	for (int i = 0; i < RequiredClasses.Num(); i++)
	{
		if (AchievedObjectClass != nullptr)
		{
			if (RequiredActions[i] == AchievedActionType && AchievedObjectClass == RequiredClasses[i])
			{
				AcquiredQuantities[i] += 1;
			}
		}

		Recap += "\n" + RequiredClassNames[i] +
			" " + FString::FromInt(AcquiredQuantities[i]) +
			" / " + FString::FromInt(RequiredQuantities[i]);
		if (AcquiredQuantities[i] >= RequiredQuantities[i]) Achieved--;
	}
	QuestRecap->SetText(FText::FromString(Recap));
	if (Achieved <= 0)
	{
		QuestBG->SetColorAndOpacity(QualifiedColor);
		bCleared = true;
	}
	return bCleared;
}
```
RefreshQuestRecap은 퀘스트 요약을 재생성하고, 클리어 여부를 업데이트 후 반환하는 기능을 수행합니다.

```C++
void UCInventoryItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = ListItemObject;

	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
		Rarity = ID->GetRarity();
		if (IIItemManager* GM = Cast<IIItemManager>(GetWorld()->GetAuthGameMode()))
		{
			UTexture2D* T = GM->IconGetter(ID->GetIconTexture());
			ItemImage->SetBrushFromTexture(T);
		}
		if (ID->GetItemType() >= 3)
		{
			ItemQuantity->SetText(FText::FromString(FString::FromInt(ID->GetItemCount())));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
		}
		ItemType = ID->GetItemType();
	}
	if (GetOwningPlayer())
	{
		ACPlayerCharacter* tempPlayer = Cast<ACPlayerCharacter>(GetOwningPlayer()->GetCharacter());
		if (tempPlayer != nullptr) tempPlayer->InventoryOpenedEvent.BindUFunction(this, TEXT("ReleasePutItem"));
	}
}
```
ItemList에 추가된 뒤, UserWidget을 상속한 UCInventoryItem 클래스에서

아이템 데이터 오브젝트(UCInventoryItemData)의 포인터를 저장하고, 표시되는 섬네일, 중첩 수량을 조정합니다.

```C++
AMMBGameModeBase::AMMBGameModeBase()
{
	// …생략
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.PackagePaths.Add("/Game/CraftResourcesIcons/Textures/");
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);
	UTexture2D* tempTexture;
	for (FAssetData Dat : AssetData)
	{
		tempTexture = Cast<UTexture2D>(Dat.GetAsset());
		if (tempTexture == nullptr) continue;
		PreLoadedTextureMap.Add(Dat.AssetName.ToString(), tempTexture);
	}
	// …생략
}

UTexture2D* AMMBGameModeBase::IconGetter(FString IconAssetName)
{
	return PreLoadedTextureMap.Contains(IconAssetName) ? PreLoadedTextureMap[IconAssetName] : DefaultIconDroppedItem;
}
```
섬네일로 사용할 UTexture2D 오브젝트는 Gamemode의 생성자에서 미리 로드시켜 Map 형태로 저장해두어

에셋의 이름을 통해 포인터를 불러올 수 있도록 구현하였습니다.

### 1-1-2. 아이템 세부정보

![image](https://github.com/user-attachments/assets/0955c45d-66f2-4370-a2bb-35e366222c8c)

아이템 위젯 위로 마우스를 올리면 아이템의 세부 정보를 표시하는 기능을 구현하였습니다.

```C++
void UCInventoryItem::OnHovered()
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	if (PlayerState != nullptr)
	{
		PlayerState->SetState(PLAYER_INVENTORY_HOVERRING, true);
		PlayerState->SetHoverringUI(this);
	}
	
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController != nullptr)
	{
		UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
		if (ID == nullptr) return;
		UIController->ShowItemDetailUI(ID); //세부정보 출력
	}
}

void UCInventoryItem::OnUnHovered()
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	if (PlayerState != nullptr)
	{
		PlayerState->SetState(PLAYER_INVENTORY_HOVERRING, false);
		PlayerState->SetHoverringUI(nullptr);
	}
	
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	UIController->UnShowItemDetailUI(); //세부정보 숨김
}
```
아이템 위젯 클래스(CInventoryItem)의 OnHovered / UnHovered 이벤트에 함수를 바인딩하여

아이템의 세부 정보를 출력하도록 구현하였습니다.

```C++
void ACPlayerController::ShowItemDetailUI(UCInventoryItemData* ItemData)
{
	if (ItemData == nullptr) return;
	
	if (ItemDetailAsset)
	{
		if (ItemDetailUI != nullptr) UnShowItemDetailUI();
		
		UCItemDetailUI* DetailUI = CreateWidget<UCItemDetailUI>(this, ItemDetailAsset);
		if (IsValid(DetailUI))
		{
			DetailUI->SetDetail(ItemData); //아이템 정보 전달
			
			FVector2D MousePos;
			GetMousePosition(MousePos.X, MousePos.Y);
			
			DetailUI->SetPositionInViewport(MousePos);
			DetailUI->AddToViewport(1);
			DetailUI->SetVisibility(ESlateVisibility::HitTestInvisible);
			ItemDetailUI = DetailUI;
		}
	}
}
```
ShowItemDetailUI 함수는 아이템의 정보를 UI에 업데이트하고

현재 마우스 커서의 위치에 아이템 세부 정보 UI(UCItemDetailUI)를 위치시킵니다.

```C++
void UCItemDetailUI::SetDetail(UCInventoryItemData* ItemData)
{
	if (IIItemManager* GM = Cast<IIItemManager>(GetWorld()->GetAuthGameMode()))
	{
		UTexture2D* T = GM->IconGetter(ItemData->GetIconTexture());
		ItemImage->SetBrushFromTexture(T);
	}

	ItemName->SetText(FText::FromString(ItemData->GetstrName()));
	ItemPrice->SetText(FText::FromString(FString::FromInt(ItemData->GetPrice())));
	ItemDetail->SetText(ItemData->GetItemDetail());

	ItemStat* Stats = ItemData->GetItemStats();
	FString tempStat;
	FString tempStatDesc;
	bool EnterFlag = false;
	if (Stats->_AttackDamage != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("공격력");
		if (Stats->_AttackDamage > 0) tempStatDesc += "+ ";
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_AttackDamage);
		EnterFlag = true;
	}
	if (Stats->_Defence != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("방어력");
		tempStatDesc += "+ ";
		//tempStatDesc += FString::SanitizeFloat(Stats->_Defence);
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_Defence);
		EnterFlag = true;
	}
	if (Stats->_AttackSpeed != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("공격속도");
		if (Stats->_AttackSpeed > 0) tempStatDesc += "+ ";
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_AttackSpeed * 100.f);
		//tempStatDesc += FString::SanitizeFloat(Stats->_AttackSpeed * 100.f);
		tempStatDesc += "%";
		EnterFlag = true;
	}

	//Potion
	if (ItemData->GetItemType() == 5 && Stats->_HealPoint != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("체력 회복");
		if (Stats->_HealPoint > 0) tempStatDesc += "+ ";
		else tempStatDesc += "- ";
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_HealPoint);
		EnterFlag = true;
	}

	ItemStatText->SetText(FText::FromString(tempStat));
	ItemStatDescText->SetText(FText::FromString(tempStatDesc));
}
```
UCItemDetailUI의 SetDetail함수는 아이템 정보를 업데이트합니다.

공격력, 공격속도 등 장착 / 사용 시 변화하는 스탯이 있다면 표시하고

그 값이 0일 경우 표시하지 않도록 구현하였습니다.

```C++
void UCItemDetailUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D MousePos;
	GetOwningPlayer()->GetMousePosition(MousePos.X, MousePos.Y);

	int Vx, Vy;
	FVector2D DS = MainPannel->GetDesiredSize();
	GetOwningPlayer()->GetViewportSize(Vx, Vy);
	if (Vx - MousePos.X <= DS.X) MousePos.X -= DS.X - (Vx - MousePos.X); //화면 넘길 시 좌우반전

	SetPositionInViewport(MousePos);
}
```
NativeTick에서는 해당 위젯이 플레이어의 마우스 커서 위치를 따라가도록 구현하였습니다.

------

## 1-2. NPC 상호작용 시스템

![image](https://github.com/user-attachments/assets/25bb8744-e3f6-42c3-b496-8f08a44299c2)
![image](https://github.com/user-attachments/assets/ee5dd1f3-18e7-4e56-a54c-ba22bbeb878f)

```C++
void ACStaticNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			PCC->NPCInteract_ShowAndInputReady(this);
		}
	}
}
```
NPC의 Collider에 충돌할 경우 ACPlayerController의 NPCInteract_ShowAndInputReady 함수를 통해 상호작용 버튼을 화면에 표시하였습니다.

![image](https://github.com/user-attachments/assets/155f4a40-69d9-4d2d-a344-a0ff5f2cd065)
```C++
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
```
NPCInterAct_ShowAndInputReady함수는 상호작용 버튼을 Viewport로 띄워줌과 동시에

SetButtonMode함수를 호출하여 버튼에 표시되는 텍스트를 교체합니다.

```C++
void UCButtonAction::SetButtonMode(int e)
{
	ButtonMode = e;

	switch (e)
	{
	case(INTERACT_BUTTON_MODE_NPCDIALOGUE):
		NPCName->SetText(FText::FromString(TEXT("대화하기")));
		return;
	case(INTERACT_BUTTON_MODE_CLIMBROPE):
		NPCName->SetText(FText::FromString(TEXT("매달리기")));
		return;
	case(INTERACT_BUTTON_MODE_JUMPPOINTS):
		NPCName->SetText(FText::FromString(TEXT("뛰기")));
		return;
	case(INTERACT_BUTTON_MODE_PICKUPITEM):
		NPCName->SetText(FText::FromString(TEXT("줍기")));
		return;
	}
}
```
각 모드를 통해 동일한 UCButtonAction 위젯으로부터 여러개의 상호작용을 처리할 수 있도록 구현하였습니다.

```C++
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
```
NPC의 Collider와의 충돌이 해제되지 않았을 때(UCButtonAction이 아직 Viewport에 표시되고 있을 때)

E버튼을 통해 현재 버튼의 상태에 따라 상호작용을 수행하도록 구현하였습니다.

```C++
void ACPlayerController::NPCInteract_Interact()
{
	if (ButtonActionUI == nullptr) return;
	SetNPCConversationVisibility(true, ButtonActionUI->GetNPC());
	NPCInteract_UnShow();
}

void ACPlayerController::SetNPCConversationVisibility(bool e, ACStaticNPC* npc)
{
	//UE_LOG(LogTemp, Log, TEXT("NPC Conversation UI Set %s"), (e ? TEXT("True") : TEXT("False")));

	if (e)
	{
		TArray<FNPCDialoguesRow*> DialogueRow = npc->GetDialogue();

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
```
NPCInteract_Interact 함수 호출 시 NPC에 저장되어 있는 DialougRow들을

NPC대화 위젯(NPCConversation)에 전달하고 Viewport에 해당 위젯을 띄워줍니다.

```C++
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

	if (InVisibility == ESlateVisibility::Visible)
	{
		if (GetWorld()->GetTimerManager().TimerExists(SwingbyTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(SwingbyTimerHandle);
			AllowInput = false;
			InSwingbyTime = 0.f;
		}
		ShoppingBox->SetVisibility(ESlateVisibility::Hidden);
		NPCLineBox->SetVisibility(ESlateVisibility::Visible);
		TeleportableListBox->SetVisibility(ESlateVisibility::Hidden);
		QuestListBox->SetVisibility(ESlateVisibility::Hidden);
		QuestRewardBox->SetVisibility(ESlateVisibility::Hidden);
		SetLineFromDialogues(0);
	}
}
```
UCNPCConversation의 SetVisibility를 Override하여 Viewport에 띄워질 때 각 패널들의 Visibility를 초기화하고,

화면에 나타낼 대사의 인덱스(초기 0)를 지정합니다.

### 1-2-1. NPC 대화 진행

![image](https://github.com/user-attachments/assets/533dfadc-cfad-490f-a2c7-1e18d59fb2de)
FNPCDialoguesRow는 NPC이름, 대사, 그리고 각 버튼의 목적지가 담긴 열(*_POSTLINE)으로 구성되어 있습니다.

```C++
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
```
각 *_POSTLINE은 버튼 상호작용 시 이동할 FNPCDialoguesRow의 인덱스를 담고 있으며,

음수일 경우 해당 버튼이 비활성화 되도록 구현하였습니다.

### 1-2-2. NPC 시점 변환
 
![ui_quest](https://github.com/user-attachments/assets/18db24dd-7f72-4418-949e-84026973985c)

```C++
AActor* ACStaticNPC::SetCameraOn(bool e, FTransform CurrentCameraTransform)
{
	NPCCameraOn = e;
	if (e)
	{
		NPCCameraFixedTransform = NPCCameraComponent->GetComponentTransform();
		NPCCameraComponent->SetWorldTransform(CurrentCameraTransform);
	}
	else NPCCameraComponent->SetWorldTransform(NPCCameraFixedTransform);
	return e? NPCCameraComponent->GetOwner() : nullptr;
}
```
NPC 대화 시작 시, 각 NPC마다 가지고 있는 CameraComponent로 플레이어가 빙의되어 있는 카메라를 교체합니다.

SetCameraOn함수를 호출하여 NPC의 카메라 위치를 플레이어의 카메라 위치로 이동시키고,

SetViewTartgetWithBlend 함수를 호출하여 카메라를 NPC의 카메라로 교체합니다.

```C++
void ACStaticNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NPCCameraOn)
	{
		FTransform CameraTransform = NPCCameraComponent->GetComponentTransform();
		CameraTransform.SetLocation(
			FMath::Lerp(CameraTransform.GetLocation(), 
			NPCCameraFixedTransform.GetLocation(), CameraMoveSpeed)
		);
		CameraTransform.SetRotation(
			FMath::Lerp(CameraTransform.GetRotation(), 
			NPCCameraFixedTransform.GetRotation(), CameraMoveSpeed)
		);
		NPCCameraComponent->SetWorldTransform(CameraTransform);
		if (
			FMath::IsNearlyEqual(CameraTransform.GetLocation().X, NPCCameraFixedTransform.GetLocation().X, 3.f) &&
			FMath::IsNearlyEqual(CameraTransform.GetLocation().Y, NPCCameraFixedTransform.GetLocation().Y, 3.f) &&
			FMath::IsNearlyEqual(CameraTransform.GetLocation().Z, NPCCameraFixedTransform.GetLocation().Z, 3.f)
		)
		{
			NPCCameraOn = false;
		}
	}
}
```
Tick함수를 Override하여 플레이어의 카메라가 있던 위치(CurrentCameraTransform)에서

NPC의 카메라가 배치되어 있던 위치(NPCCameraFixedTransform)으로

Lerp함수를 통해 부드럽게 이동하도록 구현하였습니다.

------

## 1-3. 상점 시스템

![ui_shopin_supp](https://github.com/user-attachments/assets/f2fe17cf-02c4-4467-b018-f4522529cce6)
![ui_shop2_supp](https://github.com/user-attachments/assets/ac0f9d4d-11b1-4d6a-bbee-636b49239d90)

NPC와의 대화 중 활성화된 상점 버튼을 통해 상점에 진입할 수 있도록 구현하였습니다.

```C++
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
```
버튼 상호작용 시 ShoppingBox 패널을 활성화하고, 플레이어의 아이템과 NPC의 아이템을 각각 업데이트합니다.

![image](https://github.com/user-attachments/assets/510d6d56-3201-4a0e-ab22-99b6a1eaef8c)

ShoppinbBox는 두 개의 TileView로 구성하였고, 좌측은 NPC의 아이템을 표시하는 ItemList,

우측은 플레이어의 아이템을 표시하는 ItemList_Inventory로 구성하였습니다.

```C++
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
```
ShoppingBox_LoadPlayerInventory는 플레이어의 인벤토리를 불러와 ItemList_Inventory에 저장하는 함수입니다.

ItemList_Inventory의 주소를 PlayerController에 전달하는 기능을 수행합니다.

```C++
void ACPlayerController::SetShopInventoryItems(TObjectPtr<class UTileView>& ShopTileList)
{
	ShopTileList->ClearListItems();
	if (ItemInventory->ItemList->GetNumItems() <= 0) return;
	for (UObject* Item : ItemInventory->ItemList->GetListItems())
	{
		ShopTileList->AddItem(Item);
	}
	IIPlayerState* PS = Cast<IIPlayerState>(GetCharacter());
	if (PS == nullptr) return;
	ItemInventory->PlayerGold->SetText(FText::FromString(FString::FromInt(PS->GetPlayerGold())));
}
```
PlayerController는 전달 받은 ItemList_Inventory의 주소를 통해 인벤토리 내 모든 아이템을 순회하며

해당 TileView에 플레이어가 보유 중인 아이템을 추가하고, 소지금 또한 업데이트합니다.

![image](https://github.com/user-attachments/assets/30498e5c-7486-4118-8bea-a32793e44d20)
![image](https://github.com/user-attachments/assets/7436fc65-3a0c-49e7-86a7-c1d36292b67a)

NPC는 아이템을 인덱스 형태로 가지고 있으며 에디터에서 NPC를 배치할 때 수정 가능하도록 구현하였습니다.

```C++
void ACDynamicNPC::Initialize()
{
	ItemList.Empty();
	
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	
	for (FName PossessItemRowName : PossessItems)
	{
		UCInventoryItemData* ID = ItemManager->GetItem(PossessItemRowName);
		if (ID == nullptr) continue;
		ItemList.Add(ID);
	}
}
```

각 NPC는 BeginPlay 단계에서 아이템 인덱스를 통해 아이템 테이블에서

아이템 정보(UCInventoryItemData)를 꺼내와 ItemList배열에 저장합니다.

```C++
UCInventoryItemData* AMMBGameModeBase::GetItem(FName ItemRowName, int Count)
{
	FItemTableRow* Row = ItemTable->FindRow<FItemTableRow>(ItemRowName, FString(""));

	UE_LOG(LogTemp, Log, TEXT("Loading Item : %s"), *ItemRowName.ToString())
	if (Row == nullptr) return nullptr;
	UCInventoryItemData* D = NewObject<UCInventoryItemData>(GetWorld(), UCInventoryItemData::StaticClass(), *(Row->ItemName + FString::FromInt(ItemGetCounter++)));
	D->SetDT_RowName(ItemRowName);
	D->SetIconTexture(Row->IconTexture);
	D->SetItemClass(StaticLoadClass(UObject::StaticClass(), nullptr, *Row->ItemClass));
	D->SetItemCount(Count);
	D->SetstrName(Row->ItemName);
	D->SetPrice(Row->ItemPrice);
	D->SetItemType(Row->ItemType);
	D->SetRarity(Row->Rarity);
	D->SetItemDetail(FText::FromString(Row->ItemDetail));
	D->SetItemStats(
		Row->AttackDamage,
		Row->Defence,
		Row->AttackSpeed,
		Row->Potion_HealPoint
	);
	D->SetBulletType(Row->BulletType);
	
	return D;
}
```
아이템 테이블은 게임 모드에 저장해두어 Getter를 사용하여 불러오도록 구현하였습니다.

```C++
void ACStaticNPC::SetNPCConversationItemList(TObjectPtr<UTileView>& NPCTileList)
{
	NPCTileList->ClearListItems();
	if (ItemList.IsEmpty()) return;
	for (int i = 0; i < ItemList.Num(); i++)
		{
		if (ItemList[i] != nullptr)
		{
			NPCTileList->AddItem(ItemList[i]);
		}
	}
}
```
NPC가 nullptr이 아닐 경우 SetNPCConversationItemList 함수를 통해

판매중인 아이템에 NPC가 소유 중인 아이템을 추가하였습니다.

### 1-3-1. 상점 아이템 위젯

![image](https://github.com/user-attachments/assets/501facce-d7c1-4f29-aa1a-947b7dd83d2d)

상점에 표시되는 아이템 위젯 클래스(UCShopItem)은 인벤토리 아이템 위젯 클래스를 상속하여 구현하였습니다.

![image](https://github.com/user-attachments/assets/b2b268ab-89e0-4d2a-9701-e55ab4d69222)

아이템 아이콘의 배경은 머티리얼을 사용하여 구현하였습니다.

![image](https://github.com/user-attachments/assets/1ccbbb95-6350-47b1-b3f6-126e8d44a799)

![image](https://github.com/user-attachments/assets/a6ef12bb-b2ef-4214-9ea5-848335384e63)

**Opacity*

LinearGradient와 RadialGradient를 사용하여 가운데가 뚫려 있는 이미지를 만들었고,

Opacity로 사용하여 아이템 아이콘이 들어갈 공간을 확보하였습니다.

![image](https://github.com/user-attachments/assets/a0ba2323-1d36-4b92-b75e-24c7c8ea7a6e)

![ui_item_grade_sprite](https://github.com/user-attachments/assets/bb424255-9937-452e-9558-4fe22e84f88b)

**Sprite1*

TextureIndex를 통해 Texture2DArray를 순회하여 움직이는 이미지를 구현하였고,

이미지를 확대하여 아이템 아이콘 주변에서 빛이 나는 효과를 구현하였습니다.

![image](https://github.com/user-attachments/assets/7bfa7d1f-745a-4449-8e9c-3a7c7253b94f)

![ui_item_grade_bg](https://github.com/user-attachments/assets/8d2a98ed-4914-4576-aef6-657c955b8bb0)

**Sprite2*

TextureIndex를 재활용하여 밝기가 변화하는 그라데이션 효과를 만들었고,

아이템의 등급에 따라 색상을 변경할 수 있도록 구현하였습니다.

![image](https://github.com/user-attachments/assets/477cad67-e129-44f8-b544-e03cbf7c9a10)

![image](https://github.com/user-attachments/assets/92e5fcb6-feff-442a-8558-1e3866c01f05)

![ui_item_grade](https://github.com/user-attachments/assets/9f779b82-6d7b-46c6-92f0-bb9b082814bc)

Sprite1에 아이템의 등급 색상 + 그라데이션 효과인 Sprite2를 곱하여 상점 아이템 효과를 구현하였습니다.

```C++
void UCShopItem::OnShopButtonClicked()
{
	ClickedSec = FPlatformTime::Seconds();
	SwitchPressed(!bPressed);
}

void UCShopItem::SwitchPressed(bool Pressed)
{
	if (Pressed == bPressed) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	UCInventoryItemData* ItemDataCasted = Cast<UCInventoryItemData>(ItemData);
	if (UIController == nullptr || ItemDataCasted == nullptr) return;
	if (Pressed)
	{
		bPressed = true; 
		UIController->SetPressedButton(this);
	}
	else
	{
		bPressed = false;
		CurrentTextureIndex = 0.f;
	}
}
```

```C++
void ACPlayerController::SetPressedButton(UUserWidget* SelectedButton)
{
	NPCConversation->SetSelectedButton(SelectedButton);
}
```

```C++
void UCNPCConversation::SetSelectedButton(UUserWidget* SelectedButton)
{
	if (SelectedButton->IsA(UCShopItem::StaticClass())) 	SetSelectedShopItem(SelectedButton);
	else if (SelectedButton->IsA(UCListedQuest::StaticClass())) 	SetSelectedQuest(SelectedButton);
	else if (SelectedButton->IsA(UCUserWidget_ListedStage::StaticClass())) 	SetSelectedStage(SelectedButton);
}
```

상점 아이템 클릭 시, PlayerController를 통해 NPC대화 위젯(UCNPCConversation)의 SetSelectedButton 함수를 통해 선택된 아이템을 저장합니다.

해당 함수에서는 선택한 위젯이 상점 아이템인지, 퀘스트인지, 스테이지인지 하위 클래스를 통해 판별하여 적절한 함수를 호출합니다.

```C++
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
```

선택된 위젯을 상점 아이템(ItemList)와 플레이어의 아이템(ItemList_Inventory)를 탐색하여

SetPressed함수를 호출하여 이전에 선택된 아이템의 선택을 해제합니다.

```C++
void UCShopItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (ItemSelectSpriteMaterial != nullptr)
	{
		ItemSelectSpriteMaterial->SetScalarParameterValue("TextureIndex", CurrentTextureIndex);
		
		//UE_LOG(LogTemp, Log, TEXT("Set TextureIndex To %f"), CurrentTextureIndex);
	}

	CurrentTextureIndex += InDeltaTime * 10.f;

	if (bPressed || bHovered)
	{
		float tempMaxSize = (bPressed ? 150.f : 120.f);
		if (ItemImageSize < tempMaxSize)
		{
			ItemImageSize += 50.f * InDeltaTime / (bPressed ? 0.35f : 0.7f);
			if (ItemImageSize > tempMaxSize)
			{
				ItemImageSize = tempMaxSize;
			}
			ItemImage->SetBrushSize(FVector2D(ItemImageSize));
			ItemSelectSpriteMaterial->SetScalarParameterValue("SizeOfImage", ItemImageSize);
		}
	}
	else
	{
		if (ItemImageSize > 100.f)
		{
			ItemImageSize -= 50.f * InDeltaTime / 0.8f;
			if (ItemImageSize < 100.f)
			{
				ItemImageSize = 100.f;
			}
			ItemImage->SetBrushSize(FVector2D(ItemImageSize));
			ItemSelectSpriteMaterial->SetScalarParameterValue("SizeOfImage", ItemImageSize);
		}
	}
}
```

![ui_editor_item_grade_param](https://github.com/user-attachments/assets/c8455c79-9b54-4fb9-8652-4ae0c45639af)

상점 아이템 클래스(UCShopItem)의 NativeTick에서는 스프라이트의 인덱스(TextureIndex)를 통해

Texture2DArray내에서 이미지를 순회하여 애니메이션을 구현하였습니다.

버튼이 눌림 상태이거나(bPressed) 마우스가 올라와 있는 상태면(bHovered)

SetBrushSize를 통해 아이템 아이콘의 사이즈를 변화시키고,

SizeOfImage 변수를 증가시켜 아이템 주위 스프라이트의 크기를 변경하여 선택 / 마우스 오버되는 효과를 구현하였습니다.

### 1-3-2. 상점 구매-판매

```C++
void UCNPCConversation::OnButtonBuyClicked()
{
	PlayNPCAnimation(2);
	if (SelectedButton_ToBuy == nullptr) return;
	UCShopItem* ShopItem = Cast<UCShopItem>(SelectedButton_ToBuy);
	if (ShopItem == nullptr) return;
	if (!ShopItem->GetbPressed()) return;
	ShopItem->BuyItem();
	ShoppingBox_LoadPlayerInventory();
}

void UCNPCConversation::OnButtonSellClicked()
{
	PlayNPCAnimation(2);
	if (SelectedButton_ToSell == nullptr) return;
	UCShopItem* ShopItem = Cast<UCShopItem>(SelectedButton_ToSell);
	if (ShopItem == nullptr) return;
	if (!ShopItem->GetbPressed()) return;
	ShopItem->SellItem();
	ShoppingBox_LoadPlayerInventory();
}
```

구매 / 판매 버튼 클릭 시 해당 버튼에 바인딩된 함수를 호출하도록 하였습니다.

```C++
void UCShopItem::BuyItem()
{
	IIPlayerState* PC = Cast<IIPlayerState>(this->GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());

	if (ItemManager == nullptr) return;
	if ((PC == nullptr || PCC == nullptr) || !IsValid(ID)) return;

	int32 PlayerGold = PC->GetPlayerGold();
	int32 Price = ID->GetPrice();

	if (Price > PlayerGold)
	{
		PCC->AddAlert(FText::FromString(TEXT("Not Enough Gold")));
		return;
	}
	
	UCInventoryItemData* NewID = ItemManager->GetItem(ID->GetDT_RowName());
	if (NewID == nullptr)
	{
		PCC->AddAlert(FText::FromString(TEXT("Fail To Buy Item")));
		return;
	}
	PC->SetPlayerGold(PlayerGold - Price);
	ID->SetIsShopItem(false);
	PCC->AddInventoryItem(NewID);
	PCC->ResumeShopInventoryItems();
}
```

아이템 구매 시 BuyItem함수를 호출하여 플레이어의 골드를 비교하고 부족할 경우

PlayerController클래스에 선언한 AddAlert함수를 사용하여 경고창을 띄웁니다.

[*1-1-1. 아이템 획득*](#1-1-1-아이템-획득)에서 사용한 GetItem함수를 통해 아이템을 불러와

AddInventoryItem 함수를 호출하여 플레이어의 인벤토리에 추가하도록 구현하였습니다.

```C++
void UCShopItem::SellItem()
{
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	IIPlayerState* PC = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if ((PCC == nullptr || ID == nullptr) || !PCC->IsOnShop()) return;
	int iItemPrice = ID->GetPrice();
	
	if (ID->GetItemCount() > 1)
	{
		ID->SetItemCount(ID->GetItemCount() - 1);
	}
	else
	{
		PCC->RemoveInventoryItem(ID);
	}

	PC->GainPlayerGold(iItemPrice);
}
```

```C++
void ACPlayerController::RemoveInventoryItem(UCInventoryItemData* ItemData)
{
	if (ItemData != nullptr) ItemInventory->ItemList->RemoveItem(ItemData);
}
```

아이템 판매 시, 아이템이 중첩되어 있는 경우 수량을 감소시키고

보통의 경우 인벤토리의 TileView에서 해당 위젯을 제거합니다.

이후 플레이어의 소지금에 해당 아이템의 가격에 해당하는 재화를 추가합니다.


```C++
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
```

판매 이후 ShoppingBox_LoadPlayerInventory를 재호출하여

상점 위젯 내 아이템 리스트(ItemList_Inventory)를 초기화합니다.

## 1-4. 퀘스트 시스템

![ui_teleport](https://github.com/user-attachments/assets/f2b885c2-5330-4a5f-86f2-78f2b579017c)
![ui_quest](https://github.com/user-attachments/assets/18db24dd-7f72-4418-949e-84026973985c)

퀘스트는 NPC에게 직접 수락하는 방법과 스테이지 진입 시 자동 수락되는 두 가지 방식으로 구현하였습니다.

![image](https://github.com/user-attachments/assets/5cf45e6f-dee7-4fb6-ad7a-6527a0dbcef0)

NPC는 각자 QuestTable을 가지고 있고, 플레이어에게 부여할 수 있는 퀘스트 Index를 가지고 있습니다.

```C++
void UCNPCConversation::OnButtonQuestClicked()
{
	PlayNPCAnimation(1);
	SetLineFromDialogues(BUTTON_QUEST_POSTLINE);
	
	QuestListBox->SetVisibility(ESlateVisibility::Visible);
	QuestBox_LoadNPCQuest();
}
```

NPC 대화 창에서 활성화된 퀘스트 버튼을 클릭할 경우 QuestListBox를 화면에 표시합니다.

```C++
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
```

![image](https://github.com/user-attachments/assets/13669eb7-07a6-4690-bf91-4bed72000c08)

NPC에 저장되어 있는 퀘스트 정보(FQuestRow)를 퀘스트 위젯의 구조체(UCQuestData)에 저장하고 추가하여 리스트에 표시합니다.

```C++
void ACPlayerController::HoxyPossessClearableQuest(class ACStaticNPC* NPC, TArray<class UCQuestData*>& OutArr)
{
	TArray<UObject*> Quests = HUDOverlay->QuestList->GetListItems();
	for (UObject* Quest: Quests)
	{
		UCQuestData* QD = Cast<UCQuestData>(Quest);
		UClass* HoxyClass = QD->GetGivenNPC();
		if (HoxyClass == nullptr) continue;
		if (NPC->IsA(HoxyClass))
		{
			OutArr.Add(QD);
		}
	}
}
```

HoxyPossessClearableQuest함수를 호출하여 플레이어가 가지고 있는 퀘스트 중 해당 NPC에게 클리어가 가능한 퀘스트를 추가로 리스트에 표시합니다.

```C++
void UCListedQuest::ResumeButtonStyle()
{
	UCQuestData* QD = Cast<UCQuestData>(QuestData);
	if (QD == nullptr) return;

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	QuestState = UIController->IsPossesQuestCleared(QD->GetQuestName());
	if (!UIController->IsQualifiedQuest(QD->GetRequiredQuest()))
	{
		QuestState = 4;
	}

	USlateWidgetStyleAsset* Style;
	switch (QuestState)
	{
	case(1):
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_AlreadyHave.SlateStyle_ListedQuest_AlreadyHave"));
		break;
	case(2):
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_Cleared.SlateStyle_ListedQuest_Cleared"));
		break;
	case(3):
	case(4):
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_AlreadyCleared.SlateStyle_ListedQuest_AlreadyCleared"));
		break;
	default:
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_Normal.SlateStyle_ListedQuest_Normal"));
	}

	const FButtonStyle* btnStyle = Style->GetStyle<FButtonStyle>();

	if (USlateWidgetStyleAsset* ST = Cast<USlateWidgetStyleAsset>(Style))
	{
		BtnQuest->WidgetStyle = *btnStyle;
		SB_Normal = BtnQuest->WidgetStyle.Normal;
		SB_Pressed = BtnQuest->WidgetStyle.Pressed;
	}
}
```

화면에 표시된 모든 퀘스트 위젯에 대해 ResumeButtonStyle함수를 호출하여

퀘스트의 진행여부를 업데이트하고 위젯의 스타일을 변경합니다.

```C++
UINT32 ACPlayerController::IsPossesQuestCleared(FString QuestName)
{
	for (FString ClearedQuest : ClearedQuestArr)
	{
		if (ClearedQuest == QuestName) return QUEST_ALEARDY_CLEARED;
	}

	TArray<UUserWidget*> QuestWidgets = HUDOverlay->QuestList->GetDisplayedEntryWidgets();
	for (UUserWidget* QuestWidget : QuestWidgets)
	{
		UCQuest* WQ = Cast<UCQuest>(QuestWidget);
		if (WQ == nullptr) continue;

		if (WQ->GetQuestName() == QuestName)
		{
			if (WQ->IsCleared()) return QUEST_CLEARED;
			return QUEST_ALREADY_HAVE;
		}
	}
	return QUEST_NO_MATCH;
}
```

IsPossesQuestCleared함수는 퀘스트 이름 String 변수를 통해 플레이어가 이미 클리어한 퀘스트인지 확인합니다.

완료가능한 요건을 충족했다면(IsCleared() == true) 클리어 됐음을, 아니라면 소지중임을 나타내는 상수를 반환합니다.

![image](https://github.com/user-attachments/assets/755ca69e-aa8c-416c-8847-419cd7deb468)
![image](https://github.com/user-attachments/assets/ff895893-68d6-4ff9-b51b-99ab346bdd3d)
![image](https://github.com/user-attachments/assets/11859902-ab16-4116-bd6e-e22e3661a750)
![image](https://github.com/user-attachments/assets/b95ef314-82e3-4e07-b01e-673e00d0da1d)

반환된 상태에 따라 해당 버튼에 일치하는 스타일을 부여합니다.

### 1-4-1. 퀘스트 수락

```C++
void UCNPCConversation::SetSelectedButton(UUserWidget* SelectedButton)
{
	if (SelectedButton->IsA(UCShopItem::StaticClass())) SetSelectedShopItem(SelectedButton);
	else if (SelectedButton->IsA(UCListedQuest::StaticClass())) SetSelectedQuest(SelectedButton);
	else if (SelectedButton->IsA(UCUserWidget_ListedStage::StaticClass())) SetSelectedStage(SelectedButton);
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
```

퀘스트 위젯 클릭 시 [*1-3-1. 상점 아이템 위젯*](#1-3-1-상점-아이템-위젯)과 동일하게 SetSelectedButton을 호출하여

선택한 위젯의 포인터를 저장하고, 나머지 위젯으르 선택되지 않은 상태로 전환합니다.

```C++
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
}
```

퀘스트의 현재 상태에 따라 수락하기 버튼 클릭 시 기능이 달라지도록 구현하였습니다.

수락이 가능한 상태(QUEST_NO_MATCH)의 경우

퀘스트 정보에 저장되어 있는 DialogueIndex로 이동하여 퀘스트 내용에 따른 대화를 진행합니다.

```C++
void UCNPCConversation::OnButtonYesClicked()
{
	//Quest Select Mode
	if (SelectedButton_Quest != nullptr)
	{
		PlayNPCAnimation(2);
		UCListedQuest* ListedQuest = Cast<UCListedQuest>(SelectedButton_Quest);
		if (ListedQuest == nullptr) return;
		UCQuestData* QuestData = Cast<UCQuestData>(ListedQuest->GetQuestData());
		if (QuestData == nullptr) return;

		if (ACPlayerController* PCC = Cast<ACPlayerController>(GetOwningPlayer()))
		{
			PCC->AddQuest(QuestData);
			SelectedButton_Quest = nullptr;

			SetLineFromDialogues(BUTTON_YES_POSTLINE);
			return;
		}
		UE_LOG(LogTemp, Error, TEXT("QUEST NOT SELECTED ERORR"));
		OnButtonLeaveClicked();
	}
}
```

대화 진행 중 수락하기 버튼을 통해 퀘스트를 수락할 경우 AddQuest함수를 호출하여 퀘스트를 추가합니다.

```C++
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
```

![image](https://github.com/user-attachments/assets/3a8eef1c-c186-4e56-970a-e51177ce222a)

플레이어의 QuestList에 UCQuestData 오브젝트를 추가하여 화면에 표시하였습니다.

퀘스트 수락 시 QuestInitializeIndex를 통해 특정 함수를 호출 할 수 있도록 구현하였습니다.

```C++
void ACPlayerCharacter::QuestInitialize(int e)
{
	QuestComponent->OnQuestInitialize(e);
}
```

```C++
void UQuestComponent::OnQuestInitialize(int InitIndex)
{
	switch (InitIndex)
	{
	case(0):
		Init_Quest0();
		return;
	case(1):
		Init_Quest1();
		return;
	case(2):
		Init_Quest2();
		return;
	case(3):
		Init_Quest3();
		return;
	case(4):
		Init_Quest4();
		return;
	case(5):
		Init_Quest5();
		return;
	case(6):
		Init_Quest6();
		return;
	case(7):
		Init_Quest7();
		return;
	case(8):
		Init_Quest8();
		return;
	case(9):
		Init_Quest9();
		return;
	default:
		return;
	}
}
```

QuestInitializeIndex가 지정되어 있다면 플레이어 캐릭터에 Attach되어 있는 QuestComponent에서

해당 Index에 해당하는 함수를 호출합니다.

```C++
void ACPlayerController::StartBattleMap()
{
	UCGameInstance* GInstance = Cast<UCGameInstance>(GetGameInstance());
	ACStageGameMode* GM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	
	//…생략

	// Add Hunt Quest
	FQuestsRow* QR = GM->GetQuestbyIndex(GInstance->BattleQuestRowIndex);
	if (QR != nullptr)
	{
		AddQuest(QR);

		// Find Player Spawn Point
		AActor* StartPoint = GetWorld()->GetAuthGameMode()->FindPlayerStart(this, QR->QuestStartPoint);
		if (StartPoint != nullptr)
		{
			GetCharacter()->SetActorLocation(StartPoint->GetActorLocation());
			GetCharacter()->SetActorRotation(StartPoint->GetActorRotation());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Specified Spawn Point"));
		}

		if (HUDOverlay != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("PlayerController::StartBattleMap : Throw Stage Start UI - %s"), *QR->QuestName);
			HUDOverlay->ThrowStageStartUI(QR->QuestName);
			GM->PlaySoundAtLocation(FVector::ZeroVector, SE_STAGE_STAGE_ENTRANCE);
		}
	}
	//…생략
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
```

스테이지 시작 시(BeginPlay) 게임 인스턴스에 저장된 퀘스트 인덱스를 통해 퀘스트 정보를 불러오고

AddQuest함수를 호출하여 자동으로 퀘스트가 수락되도록 구현하였습니다.

### 1-4-2. 퀘스트 완료

```C++
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
}
```

완료된 퀘스트(QUEST_CLEARED)를 선택하고 수락하기를 클릭할 경우 퀘스트 보상을 지급하는 DialougeIndex로 이동합니다.

```C++
void UCNPCConversation::SetLineFromDialogues(int e)
{

	if (Dialogues.IsValidIndex(e))
	{
		FNPCDialoguesRow* Row = Dialogues[e];

		//…생략

		BUTTON_REWARD_POSTLINE = Row->BUTTON_REWARD_POSTLINE;

		if (BUTTON_REWARD_POSTLINE >= 0) OpenQuestRewardBox();

		//…생략
	}
}
```

대화 진행 중 BUTTON_REWARD_POSTLINE이 양수일 경우 OpenQuestRewardBox를 호출합니다.

```C++
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
}
```

![image](https://github.com/user-attachments/assets/23054130-e6fe-4f39-b5a4-5779fb36499e)

![image](https://github.com/user-attachments/assets/5edeb1eb-bd3b-40d9-8fb0-5f5fa194ab02)

OpenQuestRewardBox는 퀘스트 데이터에 저장되어 있는 아이템 코드(QuestRewards)와

아이템 수량(QuestRewardsQuantity)를 통해 아이템을 불러오고,

QuestRewardBox의 QuestRewardItemList에 추가하여 보상으로 수령이 가능한 아이템을 화면에 표시하였습니다.

```C++
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
```

수령 버튼 클릭 시 QuestRewardItemList에 있는 아이템들을 획득하도록 구현하였습니다.

## 1-5. 스테이지 선택 시스템

![ui_teleport](https://github.com/user-attachments/assets/dab3d350-746a-478f-a357-05c80f920b11)

NPC를 통해 스테이지를 선택하고 진입할 수 있는 UI를 구현하였습니다.

```C++
class MMB_API ACPortalNPC : public ACStaticNPC, public IIPortalNPC
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UDataTable* MapTable;

public:
	virtual void GetTeleportableMaps(TArray<struct FTeleportableMapMonsterTableRow*>& Arr) override;

};
```

![image](https://github.com/user-attachments/assets/84863bf1-549a-4000-8672-fa36cb4c0a8c)

ACPortalNPC는 이동이 가능한 스테이지 목록인 MapTable을 가지고 있습니다.

MapTable은 표시될 이름과 스테이지 배경 텍스쳐, 몬스터 텍스쳐, 이동할 레벨, 이동 시 자동 수락되는 퀘스트를 담고 있습니다.

```C++
void UCNPCConversation::OnButtonYesClicked()
{
	//…생략
	else // Teleport Map Select Mode
	{
		if (IIPortalNPC* TNPC = Cast<IIPortalNPC>(NPC))
		{
			SelectableMapArr.Empty();
			TNPC->GetTeleportableMaps(SelectableMapArr);

			TeleportableListBox->SetVisibility(ESlateVisibility::Visible);

			if (SelectableMapArr.Num() >= 1)
			{
				for (FTeleportableMapMonsterTableRow* SelectableMap : SelectableMapArr)
				{
					UCTeleportableMapData* temp = NewObject<UCTeleportableMapData>(this, UCTeleportableMapData::StaticClass(), SelectableMap->DisplayLevelName);
					StageList->AddItem(temp);
				}
			}
		}
		
		if (BUTTON_YES_POSTLINE == Dialogues.Num()) // 마을로 복귀
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
```

![image](https://github.com/user-attachments/assets/03495ad3-a85a-43b0-9d18-08459ec479db)

수락하기 버튼을 통해 스테이지 선택 위젯으로 진입할 수 있습니다.

NPC에게 저장되어 있는 스테이지 정보를 SelectableMapArr에 불러온 뒤 StageList에 추가하여 화면에 표시합니다.

```C++
void UCUserWidget_ListedStage::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	MapName = ListItemObject->GetName();
	StageName->SetText(FText::FromString(MapName));

	StageButton->OnClicked.AddDynamic(this, &UCUserWidget_ListedStage::OnButtonClicked);
}
```

![image](https://github.com/user-attachments/assets/3e6a22c0-3255-47b4-8400-416676c9fb65)

StageList에 추가된 위젯(UCUserWidget_ListedStage)는 StageList에 추가할 때 지정했던 객체의 이름만 가지고 있습니다.

```C++
void UCUserWidget_ListedStage::OnButtonClicked()
{
	SwitchPressed(!bPressed);
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController != nullptr)
	{
		UIController->SetPressedButton(this);
	}
}
```

```C++
void UCNPCConversation::SetSelectedButton(UUserWidget* SelectedButton)
{
	if (SelectedButton->IsA(UCShopItem::StaticClass())) 	SetSelectedShopItem(SelectedButton);
	else if (SelectedButton->IsA(UCListedQuest::StaticClass())) 	SetSelectedQuest(SelectedButton);
	else if (SelectedButton->IsA(UCUserWidget_ListedStage::StaticClass())) 	SetSelectedStage(SelectedButton);
}
```

```C++
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
```

[*1-3-1. 상점 아이템 위젯*](#1-3-1-상점-아이템-위젯)과 동일한 방식으로 SetPressedButton을 호출하고,

선택한 스테이지 위젯을 SelectedStage에 저장한 뒤, 해당 위젯을 제외한 위젯의 선택 상태를 해제하고,

머티리얼의 파라미터를 수정하여 스테이지 배경과 몬스터 이미지를 변경합니다.

### 1-5-1. 스테이지 선택 UI

![image](https://github.com/user-attachments/assets/33eb1d94-d733-4bbf-8525-16d278757d77)

몬스터의 섬네일은 Panner 함수를 사용하여 텍스쳐가 상하 방향으로 자연스럽게 움직이도록 하였습니다.

주변 테두리에 해당하는 Texture는 상하좌우로 움직이도록 하여 생동감 있는 UI를 구현하였습니다.

![image](https://github.com/user-attachments/assets/a935a788-6c2d-47a8-bc49-0a1fe056641f)

주변 테두리 텍스쳐는 Time변수에 따라 회전하도록 하여 완성하였습니다.

![image](https://github.com/user-attachments/assets/22a3f078-ca79-4c49-a60d-e82d71a9ce18)

![ui_stage_monster](https://github.com/user-attachments/assets/72623f89-938b-4ef3-b534-3e2dcf693c96)

테두리 텍스쳐는 RadialGradient를 사용하여 내부를 부드럽게 투명화하여서 몬스터의 섬네일이 들어갈 공간을 확보하였습니다.

몬스터의 텍스쳐와 테두리를 합쳐 머티리얼 UI로 사용하였습니다.

## 1-6. 저장 시스템

![image](https://github.com/user-attachments/assets/6f429b99-5f26-48d2-b610-d20e2cf64a3c)

```C++
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
```

스테이지 선택 후 이동 버튼 클릭 시, 게임 인스턴스에 스테이지의 데이터테이블에 저장되어 있는 QuestIndex를 저장합니다.

이후 저장한 적이 있다면 해당 세이브 슬롯에, 없다면 메모리에 캐릭터의 현재 상태를 저장합니다.

```C++
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
		SaveGameInstance->SavedLevel = FName(GetWorld()->GetName()); //->GetPathName();

		TArray<int32> QuickSlots = { -1, -1, -1 };
		FString QuickSlot1ItemName = HUDOverlay->GetItemDataOnQuickSlot(1);
		FString QuickSlot2ItemName = HUDOverlay->GetItemDataOnQuickSlot(2);
		FString QuickSlot3ItemName = HUDOverlay->GetItemDataOnQuickSlot(3);
		
		TArray<UObject*> InventoryItemsArr = ItemInventory->ItemList->GetListItems();
		UCInventoryItemData* ID;
		for (int i = 0; i < InventoryItemsArr.Num(); i++)
		{
			ID = Cast<UCInventoryItemData>(InventoryItemsArr[i]);
			if (ID == nullptr) continue;
			if (ID->GetstrName() == QuickSlot1ItemName) QuickSlots[0] = i;
			if (ID->GetstrName() == QuickSlot2ItemName) QuickSlots[1] = i;
			if (ID->GetstrName() == QuickSlot3ItemName) QuickSlots[2] = i;
		}
		SaveGameInstance->QuickSlots = QuickSlots;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
	}
}
```

SaveGame을 호출할 경우 특정 메모리 주소 혹은 저장 슬롯에 진행 상황을 저장합니다.

아이템, 장착 중인 장비, 퀵슬롯 등의 정보를 아이템 테이블의 Index 형태로 저장하였습니다.

```C++
void ACPlayerController::StartBattleMap()
{
	UCGameInstance* GInstance = Cast<UCGameInstance>(GetGameInstance());
	ACStageGameMode* GM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	
	// Set Default Save Point
	TArray<AActor*> arrOut;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SavePoint"), arrOut);
	if (arrOut.Num() > 0)
	{
		for (AActor* A : arrOut)
		{
			ACSavePoint* tempSavePoint = Cast<ACSavePoint>(A);
			IIPlayerState* IPlayerCharacter = Cast<IIPlayerState>(GetCharacter());
			if (tempSavePoint != nullptr && IPlayerCharacter != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("Set Save Point To %s"), *tempSavePoint->GetSavePointPos().ToString());
				IPlayerCharacter->SetRevivalPoint(tempSavePoint->GetSavePointPos());
			}
		}
	}
	
	// Add Hunt Quest
	FQuestsRow* QR = GM->GetQuestbyIndex(GInstance->BattleQuestRowIndex);
	if (QR != nullptr)
	{
		AddQuest(QR);

		// Find Player Spawn Point
		AActor* StartPoint = GetWorld()->GetAuthGameMode()->FindPlayerStart(this, QR->QuestStartPoint);
		if (StartPoint != nullptr)
		{
			GetCharacter()->SetActorLocation(StartPoint->GetActorLocation());
			GetCharacter()->SetActorRotation(StartPoint->GetActorRotation());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Specified Spawn Point"));
		}

		if (HUDOverlay != nullptr) //스테이지 이름, 시작 사운드
		{
			UE_LOG(LogTemp, Log, TEXT("PlayerController::StartBattleMap : Throw Stage Start UI - %s"), *QR->QuestName);
			HUDOverlay->ThrowStageStartUI(QR->QuestName);
			GM->PlaySoundAtLocation(FVector::ZeroVector, SE_STAGE_STAGE_ENTRANCE);
		}
	}

	// Deprecated
	// Set Level Clock
	if (GInstance->StartLevelClock > 0.f)
	{
		GM->InitLevelClock(GInstance->StartLevelClock * 60.f);
		UE_LOG(LogTemp, Log, TEXT("Set StartLevel Clock : %f"), GInstance->StartLevelClock);
	}
}
```

이동하는 월드가가 전투 스테이지일 경우, StartBattleMap 함수를 실행하도록 구현하였습니다.

게임 인스턴스에 저장되어 있는 퀘스트의 Index를 통해 퀘스트를 자동 수락하고,

퀘스트에 지정되어 있는 시작 포인트가 있다면 해당 지점으로 플레이어를 이동시켰습니다.

```C++
void ACPlayerController::LoadGame(int32 SaveSlot)
{
	if (SaveSlot < 0) return;
	UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Save" + FString::FromInt(SaveSlot), SaveSlot));
	AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (SaveGameInstance == nullptr || GM == nullptr) return;

	for (int i = 0; i < SaveGameInstance->SavedItemList.Num(); i++)
	{
		UCInventoryItemData* ID = GM->GetItem(SaveGameInstance->SavedItemList[i],
			SaveGameInstance->SavedItemListQ[i]);
		if (ID == nullptr) continue;
		AddInventoryItem(ID);
	}

	IIPlayerState* PC = Cast<IIPlayerState>(GetCharacter());
	if (PC == nullptr) return;

	UCInventoryItemData* W = GM->GetItem(SaveGameInstance->SavedWeapon);
	if (W)
	{
		AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(W->GetItemClass(),
			GetCharacter()->GetActorLocation(), FRotator::ZeroRotator);
		IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor);
		if (isWeapon != nullptr)
		{
			isWeapon->SetIsEquiped(true);
			isWeapon->SetWeaponName(FName(W->GetstrName()));
			isWeapon->SetAttackDamage(W->GetAttackDamage());
			isWeapon->SetItemStat(W->GetItemStats());
			isWeapon->SetBulletType(W->GetBulletType());

			PC->Equip(*spawnedActor);
		}
		EquipItem(ITEM_TYPE_WEAPON, *W);
	}

	UCInventoryItemData* M = GM->GetItem(SaveGameInstance->SavedArmor);
	if (M) EquipItem(ITEM_TYPE_ARMOR, *M);
	UCInventoryItemData* A = GM->GetItem(SaveGameInstance->SavedArtifact);
	if (A) EquipItem(ITEM_TYPE_ARTIFACT, *A);

	PC->SetPlayerGold(SaveGameInstance->SavedGold);

	int32 QuickSlotIdx = -1;
	for (int QS : SaveGameInstance->QuickSlots)
	{
		QuickSlotIdx++;
		if (QS >= 0)
		{
			UObject* tempItem = ItemInventory->ItemList->GetItemAt(QS);
			if (tempItem == nullptr) continue;
			UCInventoryItemData* tempItemData = Cast<UCInventoryItemData>(tempItem);
			if (tempItemData == nullptr) continue;

			switch (QuickSlotIdx)
			{
			case(0):
				HUDOverlay->SetQuickSlot1(tempItemData);
				break;
			case(1):
				HUDOverlay->SetQuickSlot2(tempItemData);
				break;
			case(2):
				HUDOverlay->SetQuickSlot3(tempItemData);
				break;
			default:
				break;
			}
		}
	}
}
```

모든 월드의 경우 게임 인스턴스에 저장되어 있는 슬롯 인덱스, 혹은 메모리 주소를 매개변수로 사용하여 LoadGame함수를 호출합니다.

저장되어 있는 아이템 코드를 통해 아이템을 불러오고 인벤토리 추가, 장착, 퀵슬롯 장착을 수행합니다.

![image](https://github.com/user-attachments/assets/918768b5-5cc2-4763-ab78-50997483b3cf)
# Arcane Crusader<br><br>플레이 영상

[![플레이 영상](https://img.youtube.com/vi/-hKQ6otIoGA/0.jpg)](https://youtu.be/-hKQ6otIoGA)<br><br>

# 0. 목차
- [1. UI](#1-UI)
  
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
	    + [*1-6-2. 메인 화면 배경*](#1-6-2-메인-화면-배경)
	    + [*1-6-3. 메인 화면 오브젝트*](#1-6-3-메인-화면-오브젝트)
  
	![main_supp](https://github.com/user-attachments/assets/2f56297a-2704-4731-86a4-9053e34a6743)

	* [**1-7. HUD 시스템**](#1-7-HUD-시스템)
	    + [*1-7-1. 원형 프로그레스 바*](#1-7-1-원형-프로그레스-바)
	    + [*1-7-2. 직선 프로그레스 바*](#1-7-2-직선-프로그레스-바)
	    + [*1-7-3. 무기 스위칭 UI*](#1-7-3-무기-스위칭-UI)
 
	![ui_whole_supp](https://github.com/user-attachments/assets/c4aae09e-9d13-4bdc-a5f9-0f5b09719a6e)

- [2. 전투](#2-전투)
	* [**2-1. 플레이어 State 관리**](#2-1-플레이어-State-관리)
	    + [*2-1-1. 회피 방향 지정*](#2-1-1-회피-방향-지정)
	    + [*2-1-2. NotifyState를 활용한 회피 판정 구현*](#2-1-2-NotifyState를-활용한-회피-판정-구현)
	* [**2-2. 회피 시스템**](#2-2-회피-시스템)
	    + [*2-2-1. PostProcessMaterial을 활용한 흑백 효과 구현*](#2-2-1-PostProcessMaterial을-활용한-흑백-효과-구현)
	    + [*2-2-2. 이벤트를 활용한 둔화 효과 구현*](#2-2-2-이벤트를-활용한-둔화-효과-구현)
  
	![atk_bs_evade_supp](https://github.com/user-attachments/assets/0d77c391-1872-4684-a1a7-b81bbf546fa4)

	* [**2-3. 대미지 시스템**](#2-3-대미지-시스템)
	    + [*2-3-1. Map을 활용한 몬스터별 피격 판정 구현*](#2-3-1-Map을-활용한-몬스터별-피격-판정-구현)
	    + [*2-3-2. Queue를 활용한 대미지 UI 구현*](#2-3-2-Queue를-활용한-대미지-UI-구현)
     
	* [**2-4. 아이템 드랍 시스템**](#2-4-아이템-드랍-시스템)
	    + [*2-4-1. 나이아가라 시스템을 활용한 몬스터 사망 이펙트 구현*](#2-4-1-나이아가라-시스템을-활용한-몬스터-사망-이펙트-구현)
	    + [*2-4-2. 머티리얼을 활용한 몬스터 사망 이펙트 구현*](#2-4-2-머티리얼을-활용한-몬스터-사망-이펙트-구현)

	![atk_rs_ult_supp](https://github.com/user-attachments/assets/61a85212-024a-4f96-97ef-d01e9b9b1dd4)

	* [**2-5. 공격 시스템**](#2-5-공격-시스템)
	    + [*2-5-1. 머티리얼을 활용한 무기 이펙트 구현*](#2-5-1-머티리얼을-활용한-무기-이펙트-구현)
	    + [*2-5-2. AnimNotify를 활용한 공격 연계 시스템 구현*](#2-5-2-AnimNotify를-활용한-공격-연계-시스템-구현)
	    + [*2-5-3. 여러 애니메이션을 사용한 공격 구현*](#2-5-3-여러-애니메이션을-사용한-공격-구현)

	![atk_bs_pyeong](https://github.com/user-attachments/assets/08135222-e660-438f-90cf-a55e458e2e13)
	![atk_bs_switch](https://github.com/user-attachments/assets/6d5263ff-2c25-4d35-bf89-acbef3ae8f13)

	* [**2-6. 이펙트 소환 최적화 시스템**](#2-6-이펙트-소환-최적화-시스템)
	    + [*2-6-1. 오브젝트 풀링 패턴을 활용한 최적화 시스템*](#2-6-1-오브젝트-풀링-패턴을-활용한-최적화-시스템)
  
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

### 1-6-1. 메인 화면 UI

![ui_main_load](https://github.com/user-attachments/assets/6f5dc23c-a53c-4db5-a6cc-0864e9284af3)
![ui_esc_save](https://github.com/user-attachments/assets/715ebca2-a0dc-4028-bf04-2612124dcd73)

메인화면 혹은 ESC 메뉴에서 저장 / 불러오기를 수행할 수 있도록 구현 하였습니다.

ESC 메뉴(UCESCUI)는 메인화면 UI(UCMainUI)를 상속하고 불러오기 기능을 추가하는 방식으로 구현하였습니다.

```C++
void UCMainUI::LoadSaveSlot()
{
	SaveSlotList->ClearListItems();

	for (int i = 0; i < 3; i++)
	{
		UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Save" + FString::FromInt(i), i));
		if (SaveGameInstance == nullptr) continue;
		SaveSlotList->AddItem(SaveGameInstance);
	}
}
```

불러오기 버튼 클릭 시, 세이브 파일을 순회하여 TileView(SaveSlotList)에 추가합니다.

```C++
void UCSaveFileUI::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SaveFile = Cast<UCSaveGame>(ListItemObject);
	if (SaveFile == nullptr) return;

	SaveSlotName->SetText(FText::FromString(SaveFile->SaveSlotName));
	PlayerGold->SetText(FText::FromString(FString::FromInt(SaveFile->SavedGold)));

	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;

	UCInventoryItemData* ID = ItemManager->GetItem(SaveFile->SavedWeapon);
	if (ID != nullptr) Weapon->AddItem(ID);
	ID = ItemManager->GetItem(SaveFile->SavedArtifact);
	if (ID != nullptr) Artifact->AddItem(ID);
	ID = ItemManager->GetItem(SaveFile->SavedArmor);
	if (ID != nullptr) Armor->AddItem(ID);
}
```

![image](https://github.com/user-attachments/assets/775a4149-1bb9-47a7-806e-57c04adaa3e8)

TileView의 엔트리 위젯 클래스 UCSaveFileUI는 UCSaveGame에서 장비 중인 아이템과 소지 중인 골드를 표시합니다.

```C++
void UCESCUI::OnSaveClicked()
{
	SlotSelectPanel->SetVisibility(ESlateVisibility::Visible);

	SelectSlotList->ClearListItems();

	for (int i = 0; i < 3; i++)
	{
		UCSaveGame* SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Save" + FString::FromInt(i), i));
		if (SaveGameInstance == nullptr)
		{
			SaveGameInstance = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
			SaveGameInstance->SaveIndex = i;
		}
		SelectSlotList->AddItem(SaveGameInstance);
	}
}
```

저장 기능도 비슷한 방식으로 구현하였으나, 세이브 파일이 없을 경우 UCSaveGame 오브젝트를 생성하여 추가하여,

저장된 게임이 없을 경우에도 모든 저장 공간을 선택할 수 있도록 구현하였습니다.

```C++
void UCSaveFileUI::OnButtonClicked()
{
	if (SaveFile == nullptr) return;
 
	UGameInstance* UGI = GetGameInstance();
	UCGameInstance* GI = Cast<UCGameInstance>(UGI);
	if (GI == nullptr) return;
	GI->SelectedSaveSlot = SaveFile->SaveIndex;

	FName LoadedLevel = SaveFile->SavedLevel;
	if (SaveFile->SavedLevel.IsNone())
	{
		LoadedLevel = "Startlevel";
	}

	OnLoadingScreenSet.Broadcast(LoadedLevel);

	UGameplayStatics::OpenLevel(this, LoadedLevel);

	if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
	{
		e->MainUI->SetVisibility(ESlateVisibility::Hidden);
	}
}
```

불러오기 기능은 저장된 슬롯 위젯(UCSaveFileUI)를 클릭 시,

게임 인스턴스에 해당 슬롯의 인덱스를 저장하고, UCSaveGame 오브젝트에 저장된 스테이지로 이동하도록 구현하였습니다.

이후 [**1-6. 저장 시스템**](#1-6-저장-시스템)에서 서술한 것과 같이 BeginPlay단계에서 LoadGame 함수를 호출합니다.

```C++
void UCSaveFileSelectUI::OnButtonClicked()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());

	if (UIController == nullptr) return;
	UIController->SaveGame(SaveFile->SaveIndex);

	UIController->AddAlert(FText::FromString("Saved"));
}
```

동일한 위젯(UCSaveFileUI)를 상속하여 UCSaveFileSelectUI를 선언하였습니다.

해당 위젯 클릭 시, 위젯 클래스에 저장되어 있는 인덱스를 매개변수로 하여 SaveGame함수를 호출하여 저장을 진행합니다.

## 1-6-2. 메인 화면 배경

![object_main](https://github.com/user-attachments/assets/5c89d6a0-c404-4c35-bdc5-5b8babe46cc3)

머티리얼을 사용하여 번개가 치는 효과와 광원 효과를 표현하였습니다.

![image](https://github.com/user-attachments/assets/622d3b09-7297-424f-970a-675d6cc5bfb5)
![image](https://github.com/user-attachments/assets/be9fa3f5-cea5-44ff-8fa0-0421f12a8237)

![image](https://github.com/user-attachments/assets/6cf8f347-4f34-407b-b86c-b8d0e96f68bb)

SkySphereMaterial에 RadialGradient를 사용한 광원 효과를 추가하였습니다.

![image](https://github.com/user-attachments/assets/bf26326b-853f-4c35-99f4-d72b348f0b55)

![lighting1](https://github.com/user-attachments/assets/8fcd37f5-69e9-42e5-ba6b-1af135dbf60d)

Texture2DArray를 순회하며 번개가 내리치는 GIF 이미지를 재생하는 텍스쳐를 만들었습니다.

![image](https://github.com/user-attachments/assets/0e53dc92-62da-4dae-9895-04e6e3af3fed)

Time 변수를 사용하여 번개 이펙트가 끝나는 순간, 광원 효과를 추가한 Globe_Glow로 교체하도록 하여

간헐적으로 번개가 내리치는 배경을 구현하였습니다.

## 1-6-3. 메인 화면 오브젝트

![image](https://github.com/user-attachments/assets/91f945db-96b8-4cc3-b73e-cecfae73a09a)

스플라인 액터를 사용하여 오브젝트들을 회전시키는 장식을 구현하였습니다.

```C++
void ACMainWeaponFloatingSpline::BeginPlay()
{
	Super::BeginPlay();
	RotateActorsLocation.SetNum(RotateActors.Num());
	for (int i = 0; i < RotateActorsLocation.Num(); i++)
	{
		RotateActorsLocation[i] = 1.f / RotateActorsLocation.Num() * i;
		UE_LOG(LogTemp, Log, TEXT("%f"), RotateActorsLocation[i]);
	}
	FloatingObject->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepWorldTransform);

	FirstLocation = SplineComponent->GetRelativeLocation();
}
```

![image](https://github.com/user-attachments/assets/3de84063-951a-4d2e-8e90-02066e403073)

에디터에서 회전시킬 오브젝트를 추가할 수 있도록 구현하였고, 추가된 오브젝트들의 위치를 배열에 저장합니다.

```C++
void ACMainWeaponFloatingSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RotateActors.Num() < 1) return;

	//float temp;
	for (int i = 0; i < RotateActors.Num(); i++)
	{
		RotateActorsLocation[i] += DeltaTime * FMath::Max(FMath::Sin(RotateActorsLocation[i] * PI) / 2.f, 0.12f);
		if (RotateActorsLocation[i] > 1.f) RotateActorsLocation[i] -= 1.f;

		RotateActors[i]->SetActorLocation(SplineComponent->GetLocationAtTime(
			RotateActorsLocation[i],
			ESplineCoordinateSpace::World)
		);
		FRotator temp = RotateActors[i]->GetActorRotation();
		temp.Yaw = RotateActorsLocation[i] * 360.f;
		RotateActors[i]->SetActorRotation(temp);
	}
	if (FloatingObject == nullptr) return;
	ClockTicking += DeltaTime * FMath::Max(FMath::Sin((ClockTicking > FloatingTime / 2.f ? FMath::Abs(ClockTicking - FloatingTime) : ClockTicking) / FloatingTime * 2.f * PI) / 2.f, 0.1f);
	if (ClockTicking > FloatingTime) ClockTicking -= FloatingTime;
	FVector NextLocation = FVector(FirstLocation.X, FirstLocation.Y, FirstLocation.Z + (ClockTicking > FloatingTime / 2.f ? FMath::Abs(ClockTicking - FloatingTime) : ClockTicking) * 20.f);
	SplineComponent->SetRelativeLocation(NextLocation);
	
}
```

사인 함수를 사용하여 시작과 끝나는 지점 근처에서 오브젝트의 회전 속도가 느려지도록 구현하였습니다.

가운데에서 상하운동을 하는 FloatingObject 또한 사인함수를 사용하여 부드럽게 움직이도록 하였습니다.

## 1-7. HUD 시스템

![ui_whole](https://github.com/user-attachments/assets/844affde-9df2-4313-bf60-cbef793b75a7)

무료 GIF 이미지 에셋과 블루프린트 머티리얼을 활용하여 UI를 제작하였고, C++ 스크립트를 통해 상호작용을 구현하였습니다.

### 1-7-1. 원형 프로그레스 바

![ui_status_hp](https://github.com/user-attachments/assets/51157959-4bec-40f2-a69e-6c766ce8ff7c)

체력, 스테미나, 궁극기 충전량을 표시하는 UI를 구현하였습니다.

![image](https://github.com/user-attachments/assets/cf5b1c01-4aea-4631-9a78-c83ec75206e6)

![image](https://github.com/user-attachments/assets/976bfd0d-fd91-4701-9ee1-3d9cb1a7de81)

![image](https://github.com/user-attachments/assets/77dd021b-2ee8-46d3-8567-0c2c63ae2400)

![image](https://github.com/user-attachments/assets/bc71ea2a-dd7f-44d5-b7a7-a4ca9b97e7bf)

두 RadialGradient를 사용해서 원형의 텍스쳐를 만들었고,

12시에서 시계방향으로 1부터 0의 값을 갖는 CircularGradient를 만들었고,

특정 변수를 더하여 변수에 따라 시계방향으로 차오르는 원형의 게이지를 구현하였습니다.

![image](https://github.com/user-attachments/assets/00d2115e-9a68-41cb-9d41-3cc8260e8705)

![image](https://github.com/user-attachments/assets/e0bcf8dc-40a3-4460-9eca-7906a8dda025)

위 텍스쳐와 배경 텍스쳐를 사용하여 원형의 체력바를 구현하였습니다.

![image](https://github.com/user-attachments/assets/21ac56e3-6652-4037-81a2-86873580aeb3)

![image](https://github.com/user-attachments/assets/190ed78a-1f54-4d30-8099-a2b75f123162)

현재 체력에 최근에 입은 대미지를 더한 값을 통해 만든 원형의 게이지에

현재 체력으로 만든 게이지를 빼서 최근에 입은 대미지에 해당하는 Mask를 구현하였습니다.

![image](https://github.com/user-attachments/assets/be9b8e76-8db5-4130-9b05-804c19af7f63)

![image](https://github.com/user-attachments/assets/7200d088-14d9-4eb7-a6b4-8b30e69168a0)

유사한 방식으로 구현한 체력, 최근 입은 대미지, 스태미나,

그리고 수직으로 만든 궁극기 게이지 텍스쳐를 합쳐 최종 텍스쳐를 구현하였습니다.

![image](https://github.com/user-attachments/assets/042e9837-2098-4bdc-883b-64d70b9e3ee7)

![image](https://github.com/user-attachments/assets/f0b9c42b-a3bb-4412-b072-907f21984080)

RadialGradient를 이용하여 Segmentation 변수에 따라 원형으로 공간을 구분짓는 텍스쳐를 구현하였습니다.

![image](https://github.com/user-attachments/assets/924192ea-a84e-4210-bd07-1339e8118953)

![image](https://github.com/user-attachments/assets/b3f281db-4bcb-4f34-9ddd-f6ee1b94f2ca)

체력, 스태미나에 각각의 Segmentation을 지정하여 체력, 스태미나의 크기에 비례해서

공간을 나눌 수 있도록 구현하였습니다.

![image](https://github.com/user-attachments/assets/3f8a8852-ad4e-4b82-b62d-e09835b23e92)
![ui_status_hp](https://github.com/user-attachments/assets/51157959-4bec-40f2-a69e-6c766ce8ff7c)

궁극기 충전량에 해당하는 텍스트와 원형으로 회전하는 텍스쳐를 합쳐 블루프린트 위젯으로 사용하였습니다.

```C++
void UCUserWidget_CircularProgressBar::AddRecentDamage(float Damage)
{
	RecentDamageSum += Damage;
	bEraseRecentDamage = false;
	GetWorld()->GetTimerManager().ClearTimer(RecentDamageTimer);
	GetWorld()->GetTimerManager().SetTimer(RecentDamageTimer, FTimerDelegate::CreateLambda([&] {
		bEraseRecentDamage = true;
		}), 2.f, false
	);
}

void UCUserWidget_CircularProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	ProgressTextureIndex += 10 * InDeltaTime;
	if (ProgressTextureIndex > 24) ProgressTextureIndex = 0.f;
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("ProgressTextureIndex"), ProgressTextureIndex);

	if (bEraseRecentDamage && RecentDamageSum > 0.f)
	{
		RecentDamageSum -= RecentDamageSum * InDeltaTime * 0.6f;
		RecentDamageSum = RecentDamageSum < 0.f ? 0.f : RecentDamageSum;
	}
}
```

최근에 대미지를 입었을 경우, RecentDamageSum에 입은 대미지를 더한 뒤

타이머를 사용하여 2초 후 bEraseRecentDamage변수를 True로 설정합니다.

NativeTick 함수에서는 bEraseRecentDamage 변수가 True일 경우

RecentDamageSum의 값을 줄여 최근에 입은 대미지가 줄어들도록 구현하였습니다.

### 1-7-2. 직선 프로그레스 바

![ui_gauge_whole](https://github.com/user-attachments/assets/048738ac-68b3-406c-b789-e22adc111c34)
![ui_gauge_whole_b](https://github.com/user-attachments/assets/b6f7a26c-2b2c-4de8-a79f-ab0d6519e616)

특정 모드에 진입했을 때 변화하는 게이지를 구현하였습니다.

![image](https://github.com/user-attachments/assets/325b7772-9cc1-4a68-9bc9-8b681b512db8)

![image](https://github.com/user-attachments/assets/d44204cd-74ec-478c-86d8-7d82df771d0c)

가로로 진행되는 프로그레스 바를 구현하였습니다.

![image](https://github.com/user-attachments/assets/c7a6338a-118b-48e5-a214-709af11baa04)

![image](https://github.com/user-attachments/assets/ba869b59-11d9-4c08-8f3b-743723b67416)

RadialGradient를 사용해서 프로그레스 바의 경계에 위치하는 원 형태의 텍스쳐를 구현하였습니다.

![image](https://github.com/user-attachments/assets/2ba32fb8-4ecf-48c6-8937-72fae0311d07)

해당 경계 UV좌표를 사용해서 해당 위치에 불타오르는 텍스쳐를 배치하였습니다.

![image](https://github.com/user-attachments/assets/1d332a30-a603-4091-bc1e-fab11bf5e0c7)

프로그레스 바의 경계에 BruteMode 변수에 따라 원 형태의 텍스쳐와 불타오르는 텍스쳐가 위치하도록 구현하였습니다.

![image](https://github.com/user-attachments/assets/ddb7377d-f3e7-43b0-852e-2b115879d510)
![image](https://github.com/user-attachments/assets/a4f236c3-1320-4c0d-bc56-ae6d38528141)

경계 텍스쳐와 프로그레스 바를 합쳐 두 가지 버전의 텍스쳐를 구현하였습니다.

![image](https://github.com/user-attachments/assets/0cbd1801-6880-4d0e-8fa4-95c8be804fcf)
![image](https://github.com/user-attachments/assets/0277a942-6511-438f-ad26-d2b9069a0574)

![image](https://github.com/user-attachments/assets/9d1da2c0-8ff0-4c68-9410-0c2d1ad23870)
![image](https://github.com/user-attachments/assets/a6710eec-d396-448c-8e67-d4bede2f577f)

해당 텍스쳐에 BruteMode에 따라 서로 다른 텍스쳐를 곱해서 최종 텍스쳐를 완성하였습니다.

![image](https://github.com/user-attachments/assets/8e090aef-6193-4e4a-a2e9-2c102c47b490)

원본 텍스쳐를 Opacity와 경계로 사용해서 게이지부분을 완성하였습니다.

![image](https://github.com/user-attachments/assets/20c19b3b-a47d-4f38-988f-c264d2118d2f)

![image](https://github.com/user-attachments/assets/81aa8a31-4cc3-4ddd-bfbb-b46cba0405b8)

구형의 물체가 타오르는 이미지에 오브가 들어갈 공간을 만들어 사용하였습니다.

![image](https://github.com/user-attachments/assets/1708b245-3557-4a0e-bf56-619377bed0fc)

![image](https://github.com/user-attachments/assets/edb12f38-e0ab-40b0-bb0a-31966036d131)

Cooldown 파라미터에 비례해서 진행되는 원형의 Progressbar를 사용해서 쿨타임을 표현하였습니다.

![image](https://github.com/user-attachments/assets/8f3d5550-bcec-451f-9dd9-b4a748690ef9)

최종적으로 BruteMode 변수에따라 표시되는 텍스쳐가 달라지는 오브를 구현하였습니다.

![image](https://github.com/user-attachments/assets/f09ae871-0570-4a63-8bc9-6793042ef1d2)
![ui_gauge_whole](https://github.com/user-attachments/assets/048738ac-68b3-406c-b789-e22adc111c34)

블루프린트 위젯을 사용해서 게이지와 오브를 합쳐 완성하였습니다.

![ui_ball](https://github.com/user-attachments/assets/0e8068d9-2c53-4520-a8ef-209235414efd)

![ui_gauge](https://github.com/user-attachments/assets/0dcc14e2-6b98-4358-9e38-b138ea95291f)

머티리얼 인스턴스의 파라미터를 조정하여 UI의 상태를 조절할 수 있도록 구현하였습니다.

### 1-7-3. 무기 스위칭 UI

![atk_rs_switch](https://github.com/user-attachments/assets/0034ddae-fac2-40d8-9a74-f7dc564cca2d)

![image](https://github.com/user-attachments/assets/72a751dd-f5a1-4cd0-9ed1-92ce9e7a3ae3)

무기의 상태에 따라 탄환의 종류를 달리하였고, 모든 탄환의 상황을 나타내는 UI와

탄환을 변경하는 과정에서의 움직임을 구현하였습니다.

![image](https://github.com/user-attachments/assets/3af10305-0a50-4106-b54d-9403fbbfa22b)

![image](https://github.com/user-attachments/assets/d2770d5a-59c2-4344-9c6c-2d092f2e63f5)

각 오브는 Clock값에 따라 위치가 결정되도록 구현하였습니다.

해당 시계에 위치하게끔 Clock값을 조정하여 세 오브의 UV좌표를 계산하였습니다.

![image](https://github.com/user-attachments/assets/26f16fcf-2841-4408-891d-b8bab8874687)

Clock값에 따라 시계방향으로 위치가 변하고, 원점으로부터 특정 거리만큼 떨어진 UV 좌표를 만들었습니다.

![image](https://github.com/user-attachments/assets/6b24b77d-edbc-4b88-a00d-d078e80a26e7)
![image](https://github.com/user-attachments/assets/db8ab571-f1f7-456c-80c3-bcabf331e460)

해당 위치(OrbTexCoord)에 방울 형태의 텍스쳐와 총기 아이콘을 흑백화 시킨 텍스쳐를 위치시켰습니다.

![image](https://github.com/user-attachments/assets/ff4ef166-9829-4ef2-9149-b707c3215e11)

해당 UV 좌표에서 텍스쳐가 회전하도록 한 UV 좌표도 구현하였습니다.

![image](https://github.com/user-attachments/assets/04728f12-a04a-48e3-81d1-42cf3343a5c1)

해당 위치에는 오브를 배치하여 위치에 따라 회전하도록 하였습니다.

![image](https://github.com/user-attachments/assets/0282fb47-2c26-44bd-bc9b-491adb70b802)

![image](https://github.com/user-attachments/assets/7d1c7a65-deda-406e-a78f-3dda4b3dc750)

실린더 모양의 텍스쳐와 그를 변형시킨 텍스쳐, 마법진 모양의 텍스쳐를 합쳐 원하는 실린더의 형태를 구현하였습니다.

![image](https://github.com/user-attachments/assets/b628d0d2-d2f4-4ab2-bd2a-49503a4279bb)

![image](https://github.com/user-attachments/assets/148db2b4-84e5-4f9b-808d-a302ee8e8fc2)

오브의 위치를 나타내는 UV 좌표를 사용해서 0 - 1 사이의 게이지를 구현하여 해당 탄환의 잔탄수를 표현하였습니다.

![image](https://github.com/user-attachments/assets/6d7a3773-b54f-4c56-906d-77ef3e02772a)

![image](https://github.com/user-attachments/assets/598f4d00-7119-44bd-bd92-47bdc0b8300e)

Lerp를 사용해서 게이지가 차오른 부분은 특정 색상으로, 나머지는 흑백으로 곱해주었습니다.

최종 값에 총기 텍스쳐를 빼서 그림자 효과를 추가하였습니다.

![image](https://github.com/user-attachments/assets/a00e2421-075a-4c56-b53a-018cfa44af50)

![image](https://github.com/user-attachments/assets/378958b4-f13d-4e2b-a3ed-454a3d6195ad)

Clock값에 따라 서로 다른 위치에 위치한 세 오브와 실린더 모양의 텍스쳐를 합쳐 최종 텍스쳐를 구현하였습니다.

```C++
void UCUserWidgetPlayerHUD::DoRifleSelectBarrelRoll()
{
	if (BarrelRollLeft > 0) return;
	BarrelRollLeft += 2;
}
```

무기 스위칭 시, DoRifleSelectBarrelRoll 함수를 호출하여 실린더를 회전시키는 효과를 구현하였습니다.

```C++
void UCUserWidgetPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// …생략
	if (BarrelRollLeft > 0)
	{
		if (RifleSelectMaterial != nullptr)
		{
			CylinderAngle += BarrelRollLeft % 2 > 0 ? (InDeltaTime * 1.3f) : -(InDeltaTime * 3.5f);

			if (CylinderAngle < -0.5f)
			{
				CylinderAngle = -0.5f;
				BarrelRollLeft--;
			}
			else if (CylinderAngle > 0.f)
			{
				CylinderAngle = 0.f;
				BarrelRollLeft--;
			}
			//UE_LOG(LogTemp, Log, TEXT("CylinderAngle : %f"), CylinderAngle);
			RifleSelectMaterial->SetScalarParameterValue("Clock", CylinderAngle);
		}
	}
}
```

![image](https://github.com/user-attachments/assets/2ce57911-ecdf-4b76-be81-34a2fb6e38f4)

BarrelRollLeft의 값이 증가할 경우 NatvieTick에서 스위칭 UI의 Clock 값을 변화시켜

시계방향, 반시계방향으로 2회 회전하도록 구현하였습니다.

```C++
void ACRifleStaff::Tab_Triggered(AttackResult& AttackResult)
{
	SetBulletType((BulletType + 1) % 3);
	//…생략
}

void ACRifleStaff::SetBulletType(int32 e)
{
	BulletType = e;

	switch (BulletType)
	{
	case(RIFLESTAFF_BULLET_RIFLE):
		AttackRange = 3000.f;
		BulletSpeed = 120.f;
		ConstAttackCoolDown = 0.8f * (1 - ItemStatus->_AttackSpeed);
		break;
	case(RIFLESTAFF_BULLET_SHOTGUN):
		AttackRange = 500.f;
		BulletSpeed = 60.f;
		ConstAttackCoolDown = 1.4f * (1 - ItemStatus->_AttackSpeed);
		break;
	case(RIFLESTAFF_BULLET_MACHINEGUN):
		AttackRange = 2500.f;
		BulletSpeed = 90.f;
		ConstAttackCoolDown = 1.1f * (1 - ItemStatus->_AttackSpeed);
		break;
	default:
		break;
	}

	RifleOraEffect->SetWeaponEffect(BulletType);
}
```

ACRifleStaff에서는 현재 탄환의 타입을 변경합니다.

```C++
void ACPlayerCharacter::UpdateHUDStates()
{
	//…생략
	if (ACRifleStaff* RS = Cast<ACRifleStaff>(WeaponEquipped))
	{
		PCC->SetAimSpriteBlur(GetState(PLAYER_AIMING) ? 0.f : 10.f);
		// Rifle Select UI Update
		FVector LeftBullets;
		RS->GetLeftBullet(LeftBullets);
		//UE_LOG(LogTemp, Log, TEXT("[%f, %f, %f]"), LeftBullets.Y, LeftBullets.X, LeftBullets.Z);
		int32 CurrBulletType = RS->GetBulletType();
		PCC->SetRifleSelectCylinder(LeftBullets, FVector(CurrBulletType, (CurrBulletType + 2) % 3, (CurrBulletType + 1) % 3));
		// Charge Visibility
		if (RS != nullptr && RS->GetBulletType() == 0)
		{
			float Charged = RS->GetLMBCharge();
			//UE_LOG(LogTemp, Log, TEXT("%f"), Charged);
			if (Charged < 0.05f) PCC->HUDOverlay->AimCharge->SetVisibility(ESlateVisibility::Hidden);
			else
			{
				PCC->HUDOverlay->AimCharge->SetVisibility(ESlateVisibility::HitTestInvisible);
				PCC->HUDOverlay->AimCharge->SetPercent(Charged / 2.f);
			}
		}
		else PCC->HUDOverlay->AimCharge->SetVisibility(ESlateVisibility::Hidden);
	}
}
```

PlayerCharacter클래스에서 매 Tick마다 UpdateHUDStates를 호출합니다.

ACRifleStaff에 정의되어 있는 GetLifeBullet함수를 사용해서 남은 탄환 수를 FVector에 저장합니다.

PlayerController클래스의 SetRifleSelectCylinder함수를 호출하여

남은 탄환 FVector와 현재 사용 중인 탄환, 대기중인 탄환들을 파라미터로 전달합니다.

```C++
void ACPlayerController::SetRifleSelectCylinder(FVector Bullets, FVector WeaponDisplaySequence)
{
	HUDOverlay->SetRifleBullets(Bullets);
	HUDOverlay->SetRifleSelectSequence(WeaponDisplaySequence);
}
```

플레이어의 HUD클래스에 정의되어 있는 SetRifleBullets와 SetRifleSelectSequence함수를 호출합니다.

```C++
void UCUserWidgetPlayerHUD::SetRifleBullets(FVector NewBullets)
{
	if (RifleSelectMaterial == nullptr) return;
	RifleSelectMaterial->SetVectorParameterValue("WeaponBullet", NewBullets);
}

void UCUserWidgetPlayerHUD::SetRifleSelectSequence(FVector NewSequence)
{
	if (RifleSelectMaterial == nullptr) return;
	RifleSelectMaterial->SetVectorParameterValue("WeaponShadow", NewSequence);
	RifleSelectMaterial->SetVectorParameterValue("OverlayColor0", GetRifleBulletTypeColor(NewSequence.X));
	RifleSelectMaterial->SetVectorParameterValue("OverlayColor1", GetRifleBulletTypeColor(NewSequence.Y));
	RifleSelectMaterial->SetVectorParameterValue("OverlayColor2", GetRifleBulletTypeColor(NewSequence.Z));
}

FVector UCUserWidgetPlayerHUD::GetRifleBulletTypeColor(int32 BulletType)
{
	switch (BulletType)
	{
	case(0):
		return RifleColor;
	case(1):
		return ShotGunColor;
	case(2):
	default:
		return MachineGunColor;
	}
	return FVector::ZeroVector;
}
```

![image](https://github.com/user-attachments/assets/e3dee3d6-84fa-4775-a486-c8180be4acd9)

남은 탄환은 벡터 형식으로 보관하여 Orb0, Orb1, Orb2위치에 있는 게이지의 채워지는 양을 결정합니다.

무기 아이콘(WeaponShadow)는 Texture2DArray에서의 인덱스를 변경하는 방식으로 아이콘을 교체하였습니다.

각 탄환의 대표 색상은 GetRifleTypeColor함수를 통해 FVector에 미리 저장되어 있는 상수를 반환하여

OverlayColor0, 1, 2의 값을 직접 변경하는 방식으로 구현하였습니다.

![atk_rs_switch](https://github.com/user-attachments/assets/f6e56011-8c94-4a2b-a800-ed23c0104a2a)


# 2. 전투
## 2-1. 플레이어 State 관리

```C++
//Player State
#define PLAYER_UI_INTERACTING		UINT(1) << 0
#define PLAYER_RAGDOLL				UINT(1) << 1
#define PLAYER_CANGETUP				UINT(1) << 2
#define PLAYER_ROLL_INVINCIBLE		UINT(1) << 3

#define PLAYER_INPUT_W				UINT(1) << 4
#define PLAYER_INPUT_S				UINT(1) << 5
#define PLAYER_INPUT_A				UINT(1) << 6
#define PLAYER_INPUT_D				UINT(1) << 7

#define PLAYER_ATTACKING			UINT(1) << 8
#define PLAYER_ATTACK_CANCLE_UNLOCK UINT(1) << 9
#define PLAYER_STAMINA_RUNOUT		UINT(1) << 10
#define PLAYER_ROLLING				UINT(1) << 11

#define PLAYER_DODGED				UINT(1) << 12
#define PLAYER_BS_ESCAPE_COMBO_TAB	UINT(1) << 13
//#define PLAYER_BS_JUMP_UP			UINT(1) << 14
//#define PLAYER_INPUT_TYPE_JUMP		UINT(1) << 15

//#define PLAYER_INPUT_TYPE_MOVE		UINT(1) << 16
#define PLAYER_COMBO_STACK_1		UINT(1) << 17
#define PLAYER_COMBO_STACK_2		UINT(1) << 18
#define PLAYER_COMBO_STACK_3		UINT(1) << 19

#define PLAYER_GETTINGUP			UINT(1) << 20
#define PLAYER_STAMINA_REGAIN		UINT(1) << 21
#define PLAYER_DIED					UINT(1) << 22
#define PLAYER_DRINKING_POTION		UINT(1) << 23

#define PLAYER_CLIMBING_ROPE		UINT(1) << 24
#define PLAYER_JUMPING_POINTS		UINT(1) << 25
#define PLAYER_AIMING				UINT(1) << 26
#define PLAYER_DIZZY				UINT(1) << 27

#define PLAYER_INVENTORY_HOVERRING	UINT(1) << 28
#define	PLAYER_BRUTEMODE_ORAORA		UINT(1) << 29
#define PLAYER_BRUTEMODE_COMBO_IN	UINT(1) << 30
#define PLAYER_ULT_INVINCIBLE		UINT(1) << 31

//Player Pressing Key
#define PLAYER_INPUT_LMB			UINT(1) << 0
#define PLAYER_INPUT_RMB			UINT(1) << 1

//Player Input Type Overall Check
#define PLAYER_INPUT_TYPE_CLICK		UINT(1) << 2
#define PLAYER_INPUT_TYPE_SHIFT		UINT(1) << 3

#define PLAYER_INPUT_TYPE_LOOK		UINT(1) << 4
#define PLAYER_INPUT_TYPE_JUMP		UINT(1) << 5
#define PLAYER_INPUT_TYPE_MOVE		UINT(1) << 6
```

플레이어의 현재 상태를 32비트의 정수에 저장하여 관리하였습니다.

```C++
bool ACPlayerCharacter::GetState(UINT StateType)
{
	if (State & StateType) return true;
	else return false;
}

void ACPlayerCharacter::SetState(UINT StateType, bool b)
{	
	if (GetState(StateType) ^ b)
	{
		if (b) State += StateType;
		else State -= StateType;
	}

	//Exceptions

	switch (StateType)
	{
	case(PLAYER_AIMING):
		bUseControllerRotationYaw = b;
		GetCharacterMovement()->bOrientRotationToMovement = !b;
		if (!b)
		{
			ACRifleStaff* RS = Cast<ACRifleStaff>(WeaponEquipped);
			if (RS != nullptr)
			{
				RS->SetLMBLock(false);
			}
			//AimOff.ExecuteIfBound();
		}
		break;
	default:
		break;
	}
}
```

Getter와 Setter를 구현하여 플레이어의 상태를 직접 확인하거나 수정할 수 있도록 하였습니다.

```C++
bool ACPlayerCharacter::PlayerInputCheck(int InputType)
{
	bool UICheck = !GetState(PLAYER_UI_INTERACTING);
	bool Standing = (!GetState(PLAYER_RAGDOLL) && !GetState(PLAYER_CANGETUP));
	bool GroundedButCanGetUp = GetState(PLAYER_CANGETUP) && GetState(PLAYER_RAGDOLL);
	bool notGettingUp = !GetState(PLAYER_GETTINGUP);
	bool notStaminaRunout = !GetState(PLAYER_STAMINA_RUNOUT);
	bool notClimbing = !GetState(PLAYER_CLIMBING_ROPE) && !GetState(PLAYER_JUMPING_POINTS); // or jumping
	bool notDead = !GetState(PLAYER_DIED);
	bool notAiming = !GetState(PLAYER_AIMING);
	bool EvadeEscape = (GetState(PLAYER_ATTACKING) && GetState(PLAYER_ATTACK_CANCLE_UNLOCK)) || !GetState(PLAYER_ATTACKING);
	switch (InputType)
	{
	case(PLAYER_INPUT_TYPE_SHIFT):
		if (notDead) Getup();
		else Anykey_Triggered();
		return notAiming && notDead && UICheck && (Standing || GroundedButCanGetUp) && notStaminaRunout && notClimbing && !GetState(PLAYER_ROLLING) && EvadeEscape;
		break;
	case(PLAYER_INPUT_TYPE_LOOK):
		return UICheck;
		break;
	case(PLAYER_INPUT_TYPE_CLICK):
		if (GetState(PLAYER_DRINKING_POTION))
		{
			UE_LOG(LogTemp, Log, TEXT("PLAYER_DRINKING_POTION True"));
			return false;
		}
	case(PLAYER_INPUT_TYPE_JUMP):
	case(PLAYER_INPUT_TYPE_MOVE):
		if (notDead) LazyGetUp();
		else Anykey_Triggered();
		return notDead && UICheck && Standing && notGettingUp && notStaminaRunout && notClimbing;
		break;
	default:
		return false;
	}
}
```

플레이어의 상태를 종합적으로 판단하여 특정 상황에서 특정 행동이 가능한 상황인지 판단하는 함수를 구현하였습니다.

```C++
void ACPlayerCharacter::LMBTriggered()
{
	SetKeyState(PLAYER_INPUT_LMB, true);

	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			//(this->*LMBPressedPointer)(*this);
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->LMB_Triggered(AR);
			StaminaSpend(AR.StaminaUsed);
		}
	}
}
```

버튼에 바인딩 된 함수에서 반드시 호출하여 사용가능한 상태인지 판단하도록 하였습니다.

### 2-1-1. 회피 방향 지정

```C++
void ACPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	//if (SpineCapsuleDist > 40.f) return;

	SetState(PLAYER_INPUT_W, MovementVector.Y > 0 ? true: false);
	SetState(PLAYER_INPUT_S, MovementVector.Y < 0 ? true : false);
	SetState(PLAYER_INPUT_D, MovementVector.X > 0 ? true : false);
	SetState(PLAYER_INPUT_A, MovementVector.X < 0 ? true : false);

	// NO ATTACK or ROLLING BUT AIMING IS FINE 
	if ((!GetState(PLAYER_AIMING) && GetState(PLAYER_ATTACKING)) || GetState(PLAYER_ROLLING)) return;

	// STAMINA RAN OUT OVERED
	if (GetState(PLAYER_DIZZY) && !GetState(PLAYER_STAMINA_RUNOUT))
	{
		SetState(PLAYER_DIZZY, false);
		StopAnimMontage();
	}

	//…생략

	//MOVE
	if (Controller != nullptr && PlayerInputCheck(PLAYER_INPUT_TYPE_MOVE))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (!CheckIsAtCharacter(ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X))
		{
			return;
		}

		AddMovementInput(ForwardDirection, GetState(PLAYER_AIMING) ? 
			MovementVector.Y * 0.1f : MovementVector.Y * CameraComponent->FieldOfView / 90.f);
		AddMovementInput(RightDirection, GetState(PLAYER_AIMING) ? 
			MovementVector.X * 0.1f : MovementVector.X * CameraComponent->FieldOfView / 90.f);

		float TempSpeed = GetCharacterMovement()->MaxWalkSpeed * (1 + AccMovementSpeedAcc);
		if (MaxMoveMentSpeed >= TempSpeed) GetCharacterMovement()->MaxWalkSpeed = TempSpeed;

		//UE_LOG(LogTemp, Log, TEXT("%s"), *Rotation.ToString());
	}
}
```

인풋 벡터를 사용해서 이동할 때마다 각 방향의 State를 변경하여 플레이어가 입력중인 버튼을 저장하도록 하였습니다.

```C++
void ACPlayerCharacter::ShiftTriggered()
{
	if (!PlayerInputCheck(PLAYER_INPUT_TYPE_SHIFT))
	{
		return;
	}
	
	if (Stamina <= ShiftStamina * 0.4f) return;

	SetActorRotation(GetMoveInputDesiredRotator());
	StopAnimMontage();
	if (StandToRoll.ExecuteIfBound())
	{
		SetState(PLAYER_ROLLING, true);
		Stamina -= ShiftStamina;
	}
}

FRotator ACPlayerCharacter::GetMoveInputDesiredRotator()
{
	double directionalYaw = 0.f;

	bool W = GetState(PLAYER_INPUT_W);
	bool S = GetState(PLAYER_INPUT_S);
	bool A = GetState(PLAYER_INPUT_A);
	bool D = GetState(PLAYER_INPUT_D);

	if (W && A)			directionalYaw = -45.f;
	else if (W && D)		directionalYaw = 45.f;
	else if (S && A)		directionalYaw = -135.f;
	else if (S && D)		directionalYaw = 135.f;
	else if (S)			directionalYaw = 180.f;
	else if (A)			directionalYaw = -90.f;
	else if (D)			directionalYaw = 90.f;
	else if (W)			directionalYaw = 0.f;
	else FRotator(0.f, GetActorRotation().Yaw, 0.f);
	
	return FRotator(0.f, GetBaseAimRotation().Yaw + directionalYaw, 0.f);
}
```

Shift(회피) 시, GetMoveInputDesiredRotator를 호출해서 플레이어가 보는 방향 + 입력중인 버튼을 계산합니다.

이동이 불가능하고 회피는 가능한 공격 중인 상태 등에서 입력 중인 방향으로 회피를 사용할 수 있도록 하였습니다.

![atk_bs_evade](https://github.com/user-attachments/assets/99377d2d-0100-451e-8730-7b13c81499d4)

### 2-1-2. NotifyState를 활용한 회피 판정 구현

```C++
void UCAnimNotifyState_PlayerRollInvin::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPlayerCharacter(MeshComp))
	{
		PC->SetState(PLAYER_ROLL_INVINCIBLE, true);
	}
}

void UCAnimNotifyState_PlayerRollInvin::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (PC != nullptr)
	{
		PC->SetState(PLAYER_ROLL_INVINCIBLE, false);
	}
}

bool UCAnimNotifyState_PlayerRollInvin::GetPlayerCharacter(USkeletalMeshComponent* MeshComp)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	return (PC != nullptr) ? true : false;
}
```

![image](https://github.com/user-attachments/assets/df46facc-1cd8-4c2c-99c8-61489ce8edce)

회피 애니메이션 도중 AnimNotifyState를 사용해서 PLYAER_ROLL_INVINCIBLE 상태를 true로 변경합니다.

```C++
bool ACPlayerCharacter::HitDamage(float e, ACEnemyCharacter* Attacker, FVector HitLocation, int Power)
{
	if (GetState(PLAYER_ROLL_INVINCIBLE))
	{
		if (!GetState(PLAYER_DODGED))
		{
			OnDodgedAttack();
		}
		UE_LOG(LogTemp, Log, TEXT("Player Roll Dodged"));
		return false;
	}
	else if (GetState(PLAYER_RAGDOLL) || GetState(PLAYER_GETTINGUP))
	{
		UE_LOG(LogTemp, Log, TEXT("Player in Ragdoll"));
		return false;
	}
	else if (GetState(PLAYER_ULT_INVINCIBLE))
	{
		UE_LOG(LogTemp, Log, TEXT("Player Using Ult"));
		return false;
	}

	ItemStat CurrStat = ItemStat();

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	if (UIController == nullptr) return false;
	UIController->EquippedItemStat(CurrStat);

	UE_LOG(LogTemp, Log, TEXT("Player Defence = %f"), CurrStat._Defence);
	float DeffencePer = 1 - (CurrStat._Defence / 500.f);
	if (DeffencePer <= 0.1f) DeffencePer = 0.1f;
	UE_LOG(LogTemp, Log, TEXT("Player Defence Damage = %f"), DeffencePer);
	HP -= (e * DeffencePer);
	SetState(PLAYER_UI_INTERACTING, false);
	SetLastDealingEnemy(Attacker);
	
	UIController->AddRecentDamage(e * DeffencePer / MaxHP);


	ShowDamageUI(e * DeffencePer, HitLocation, true);

	if (HP <= 0.f) return true;
	switch (Power)
	{
	case(PLAYER_HIT_REACT_STAND):
		break;
	case(PLAYER_HIT_REACT_FLINCH):
		StopAnimMontage();
		SetState(PLAYER_ATTACKING, true);
		HitReact.ExecuteIfBound();
		break;
	case(PLAYER_HIT_REACT_HITDOWN):
		StopAnimMontage();
		SetState(PLAYER_RAGDOLL, false);
		SetState(PLAYER_CANGETUP, true);
		HitDown.ExecuteIfBound();
		break;
	}
	return true;
}
```

PLAYER_ROLL_INVINCIBLE이 true일 경우 대미지를 입지 않도록 구현하였습니다.

회피 성공 시, PLAYER_DODGED를 true로 변경하고 회피 시 시전되는 스킬을 구현하였습니다.

시전된 스킬이 끝나기 전까지 PLAYER_DODGED를 true로 두어 중복으로 시전되지 않도록 하였습니다.

![atk_rs_evade](https://github.com/user-attachments/assets/a68a4a89-1c8a-4b19-93a8-c246424d717d)

## 2-2. 회피 시스템

```C++
void UCAnimNotifyState_PlayerFStep::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	ScaleValue = 20.f;
	if (PC != nullptr) Direction = PC->GetActorForwardVector();
}

void UCAnimNotifyState_PlayerFStep::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (PC != nullptr)
	{
		PC->AddMovementInput(Direction, ScaleValue, true);
	}
}
```

![image](https://github.com/user-attachments/assets/317948f0-0683-4008-904f-f75a8c051a5c)

회피 애니메이션 재생 시, 캐릭터를 전진시키는 AnimNotifyState를 구현하여 애니메이션 도중 앞으로 구르며 이동하는 효과를 구현하였습니다.

```C++
void ACPlayerCharacter::OnDodgedAttack()
{
	if (StageMaterialManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StageMaterialManager Not Found"));
		return;
	}
	StageMaterialManager->PostProcessZoom(true, GetActorLocation());
	StageMaterialManager->ExecutePlayerDodgedEvent();
	GetWorld()->GetTimerManager().ClearTimer(DodgeTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(DodgeTimerHandle, FTimerDelegate::CreateLambda(
		[&] {
			if (StageMaterialManager != nullptr) StageMaterialManager->ExecutePlayerDodgedEndEvent();
			SetState(PLAYER_DODGED, false);
			DodgeDom->SetVisibility(false);
		}
	), 3.f, false);
	DodgeDom->SetRelativeScale3D(FVector(StageMaterialManager->GetPostProcessRadius() / 100.f));
	DodgeDom->SetVisibility(true);
	SetState(PLAYER_DODGED, true);
}
```

회피 판정 시, OnDodgedAttack함수를 호출하여 주변을 암전시키고 적들의 움직임을 둔화시키는 효과를 구현하였습니다.

### 2-2-1. PostProcessMaterial을 활용한 흑백 효과 구현

```C++
void ACStageGameMode::PostProcessZoom(bool IsStart, FVector ZoomPos)
{
	if (MPC_GlobalPostProcessVolume == nullptr) return;
	if (IsStart) MPC_GlobalPostProcessVolume->SetVectorParameterValue("PlayerPos", ZoomPos);
	MPC_GlobalPostProcessVolume->SetScalarParameterValue("IsDesaturate", IsStart ? 1.f : 0.f);

	bPostProcessZoom = IsStart;
	PostProcessRadius = PostProcessMaxRadius;
}
```

게임 모드 클래스에 정의되어 있는 PossProcessZoom을 호출하여 플레이어의 현재 위치와 IsDesturate 변수를 변경합니다.

이후 흑백이 아닌 부분이 줄어드는 효과를 구현하기 위해 bPostProcessZoom 변수를 true로 변경하고,

PostProcessRadius 변수를 최대값으로 변경하였습니다.

```C++
void ACStageGameMode::Tick(float DeltaSeconds)
{
	//…생략
	if (bPostProcessZoom)
	{
		if (PostProcessRadius <= 0.f) return;

		PostProcessRadius -= PostProcessMaxRadius * DeltaSeconds / 0.1f * PostProcessRadius / PostProcessMaxRadius;
		if (PostProcessRadius < 0.f)
		{
			PostProcessRadius = 0.f;
		}
		UpdateRadius(PostProcessRadius);
	}
	//…생략
}

void ACStageGameMode::UpdateRadius(float e)
{
	if (MPC_GlobalPostProcessVolume == nullptr) return;
	MPC_GlobalPostProcessVolume->SetScalarParameterValue("Radius", e);
	UE_LOG(LogTemp, Log, TEXT("ACStageGameMode::UpdateRadius : %f"), e);
}
```

이후 Tick에서 플레이어 주변 흑백이 아닌 부분이 줄어들도록 PostProcess머티리얼 내의 Radius변수를 지속적으로 감소시켰습니다.

![image](https://github.com/user-attachments/assets/b1ddf476-8385-4dfb-93d3-0bab61efc05c)

![image](https://github.com/user-attachments/assets/130698b5-0dc2-4ef1-8209-e3eddb1e3aa7)

플레이어의 좌표 PlayerPos와 절대 월드 포지션을 비교해서 플레이어 주변 공간(In/OutMask)를 생성하였습니다.

![image](https://github.com/user-attachments/assets/5c515c07-9f38-4164-9f72-0b3f8d7f5255)

동일한 방식으로 섬의 중심으로부터 떨어진 거리를 계산해서 섬 외부 공간(Outside Island)를 생성하였습니다.

섬 내부는 단순한 세피아톤![image](https://github.com/user-attachments/assets/317948f0-0683-4008-904f-f75a8c051a5c)

회피 애니메이션 재생 시, 캐릭터를 전진시키는 AnimNotifyState를 구현하여 애니메이션 도중 앞으로 구르며 이동하는 효과를 구현하였습니다.

```C++
void ACPlayerCharacter::OnDodgedAttack()
{
	if (StageMaterialManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StageMaterialManager Not Found"));
		return;
	}
	StageMaterialManager->PostProcessZoom(true, GetActorLocation());
	StageMaterialManager->ExecutePlayerDodgedEvent();
	GetWorld()->GetTimerManager().ClearTimer(DodgeTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(DodgeTimerHandle, FTimerDelegate::CreateLambda(
		[&] {
			if (StageMaterialManager != nullptr) StageMaterialManager->ExecutePlayerDodgedEndEvent();
			SetState(PLAYER_DODGED, false);
			DodgeDom->SetVisibility(false);
		}
	), 3.f, false);
	DodgeDom->SetRelativeScale3D(FVector(StageMaterialManager->GetPostProcessRadius() / 100.f));
	DodgeDom->SetVisibility(true);
	SetState(PLAYER_DODGED, true);
}
```

회피 판정 시, OnDodgedAttack함수를 호출하여 주변을 암전시키고 적들의 움직임을 둔화시키는 효과를 구현하였습니다.

```C++
void ACStageGameMode::PostProcessZoom(bool IsStart, FVector ZoomPos)
{
	if (MPC_GlobalPostProcessVolume == nullptr) return;
	if (IsStart) MPC_GlobalPostProcessVolume->SetVectorParameterValue("PlayerPos", ZoomPos);
	MPC_GlobalPostProcessVolume->SetScalarParameterValue("IsDesaturate", IsStart ? 1.f : 0.f);

	bPostProcessZoom = IsStart;
	PostProcessRadius = PostProcessMaxRadius;
}
```

게임 모드 클래스에 정의되어 있는 PossProcessZoom을 호출하여 플레이어의 현재 위치와 IsDesturate 변수를 변경합니다.

이후 흑백이 아닌 부분이 줄어드는 효과를 구현하기 위해 bPostProcessZoom 변수를 true로 변경하고,

PostProcessRadius 변수를 최대값으로 변경하였습니다.

```C++
void ACStageGameMode::Tick(float DeltaSeconds)
{
	//…생략
	if (bPostProcessZoom)
	{
		if (PostProcessRadius <= 0.f) return;

		PostProcessRadius -= PostProcessMaxRadius * DeltaSeconds / 0.1f * PostProcessRadius / PostProcessMaxRadius;
		if (PostProcessRadius < 0.f)
		{
			PostProcessRadius = 0.f;
		}
		UpdateRadius(PostProcessRadius);
	}
	//…생략
}

void ACStageGameMode::UpdateRadius(float e)
{
	if (MPC_GlobalPostProcessVolume == nullptr) return;
	MPC_GlobalPostProcessVolume->SetScalarParameterValue("Radius", e);
	UE_LOG(LogTemp, Log, TEXT("ACStageGameMode::UpdateRadius : %f"), e);
}
```

이후 Tick에서 플레이어 주변 흑백이 아닌 부분이 줄어들도록 PostProcess머티리얼 내의 Radius변수를 지속적으로 감소시켰습니다.

![image](https://github.com/user-attachments/assets/b1ddf476-8385-4dfb-93d3-0bab61efc05c)

![image](https://github.com/user-attachments/assets/130698b5-0dc2-4ef1-8209-e3eddb1e3aa7)

플레이어의 좌표 PlayerPos와 절대 월드 포지션을 비교해서 플레이어 주변 공간(In/OutMask)를 생성하였습니다.

![image](https://github.com/user-attachments/assets/5c515c07-9f38-4164-9f72-0b3f8d7f5255)

동일한 방식으로 섬의 중심으로부터 떨어진 거리를 계산해서 섬 외부 공간(Outside Island)를 생성하였습니다.

섬 내부 공간은 단순한 흑백효과로, 외부 공간은 외곽선이 강조된 카툰 형식으로 구현하였습니다.


![image](https://github.com/user-attachments/assets/098ff6f0-513e-4951-8d9d-dc1b0c9621d9)

![image](https://github.com/user-attachments/assets/cf3509c4-b048-430f-97a8-884e6df37c4d)

SceneDepth의 상하좌우 방향에 위치한 Depth들의 평균치를 사용해서 외곽선을 구현하였습니다.

Outside Island를 사용해서 섬 외부 배경에만 적용하였습니다.

![image](https://github.com/user-attachments/assets/383b666d-f74d-4c2b-9676-363007bd8ad1)

```C++
ACPlayerCharacter::ACPlayerCharacter()
{
	//…생략
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1);
}
```

![image](https://github.com/user-attachments/assets/de367317-43f5-409a-a7fb-86e9391ec393)

플레이어의 Character는 CustomDepth를 설정하여 플레이어 캐릭터 메시와 그에 부착된 다른 메시도 적용되지 않도록 구현하였습니다.

Lerp를 사용해서 CustomDepth와 In/OutMask를 제외한 화면에

Desaturation이 적용된 PostProcessInput을 적용하여 흑백 화면을 구현하였습니다.

![image](https://github.com/user-attachments/assets/acd78ff8-9308-4a41-92f3-55e18a7a3a70)

![image](https://github.com/user-attachments/assets/b88ca20c-933b-4c8c-a5f6-1978d9591120)

섬 외부의 외곽선을 더하여 완성하였습니다.

결과적으로 회피가 발동된 직후, 플레이어 지점 주변은 컬러로 표시되고 Radius값이 줄면서 점차 전부 흑백으로 전환됩니다.

플레이어의 캐릭터 메시는 CustomDepth를 사용해서 예외로 처리해 컬러로 출력되도록 구현하였습니다.

![atk_bs_evade](https://github.com/user-attachments/assets/ba771466-8561-4077-b7fb-889aef302ed0)

### 2-2-2. 이벤트를 활용한 둔화 효과 구현

```C++
void ACStageGameMode::ExecutePlayerDodgedEvent()
{
	PlayerDodged.ExecuteIfBound();
}

void ACStageGameMode::ExecutePlayerDodgedEndEvent()
{
	PlayerDodgedEnd.ExecuteIfBound();
	PostProcessZoom(false, FVector::ZeroVector);
}
```

몬스터의 공격을 회피하여 OnDodgedAttack함수가 호출되었을 때, 게임모드 클래스에 구현되어 있는 PlayerDodged이벤트를 발생시킵니다.

```C++
void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ACStageGameMode* StageGM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	if (StageGM != nullptr)
	{
		StageGM->PlayerDodged.BindUFunction(this, "OnPlayerDodged");
		StageGM->PlayerDodgedEnd.BindUFunction(this, "OnPlayerDodgedEnd");
	}

	if (GetMesh() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACEnemyCharacter : Can Not Load Mesh"));
		return;
	}

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyCharacter::OnOverlapPlayer);
	GetMesh()->OnComponentEndOverlap.AddDynamic(this, &ACEnemyCharacter::OnOverlapEndPlayer);

	DiedFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		DiedFX, GetMesh(), FName(), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTargetIncludingScale, true, false
	);
}

void ACEnemyCharacter::OnPlayerDodged()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (AnimInst == nullptr) return;
	AnimInst->Montage_SetPlayRate(GetCurrentMontage(), 0.2f);
}

void ACEnemyCharacter::OnPlayerDodgedEnd()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (AnimInst == nullptr) return;
	AnimInst->Montage_SetPlayRate(GetCurrentMontage(), 1.f);
}
```

PlayerDodged 이벤트는 몬스터 객체의 상위 클래스인 ACEnemyCharacter에서 OnPlayerDodged 함수에 바인딩하였습니다.

OnPlayerDodged함수를 호출할 경우 현재 재생중인 Montage의 재생 속도를 낮춥니다.

```C++
void UCEnemyAnimInstance::NativeInitializeAnimation()
{
	EnemyCharacter = Cast<ACEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		OnMontageEnded.AddDynamic(this, &UCEnemyAnimInstance::SetbAttackingFree);
	}

	ACStageGameMode* StageGM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	if (StageGM != nullptr)
	{
		StageGM->PlayerDodged.BindLambda([&]() {
				PlayRate = 0.2f;
			}
		);
		StageGM->PlayerDodgedEnd.BindLambda([&]() {
			PlayRate = 1.f;
			}
		);
	}
}
```

또한, 몬스터 객체의 애님 클래스의 상위 클래스인 UCEnemyAnimInstance에서 PlayerDodged 이벤트 발생 시,

PlayRate 변수를 조정하여 이후 재생되는 Montage에도 영향을 미치도록 하였습니다.

![atk_bs_evade](https://github.com/user-attachments/assets/0e4ce5f7-e42b-4017-85fc-f4668a3b9cf4)


## 2-3. 대미지 시스템

```C++
void UCAnimNotifyState_EnemyAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ContinueAttack = true;
	EC = Cast<IIEnemyStateManager>(MeshComp->GetOwner());
	if (AttackType < 6) return;
	if (EC == nullptr) return;

	EC->SpitFireBall(false);
}

void UCAnimNotifyState_EnemyAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (!ContinueAttack) return;
	if (AttackType > 5) return;
	if (EC == nullptr) return;

	ContinueAttack = !EC->AttackHitCheck(AttackType * 2, DamageScale);
}

void UCAnimNotifyState_EnemyAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AttackType < 6) return;
	if (EC == nullptr) return;

	EC->SpitFireBall(true);
}
```

몬스터의 공격은 EnemyAttack NotifyState를 사용해서 구현하였습니다.

애니메이션에 NotifyState를 배치하고 AttackType을 지정하면 매 Tick마다 AttackHitCheck함수를 호출하여

몬스터의 특정 Bone과 플레이어와의 충돌 여부를 검사합니다.

### 2-3-1. Map을 활용한 몬스터별 피격 판정 구현

```C++
#define ENEMY_ATTACK_RHAND		0
#define ENEMY_ATTACK_RHAND_E		1
#define ENEMY_ATTACK_HEAD		2
#define ENEMY_ATTACK_HEAD_E		3
#define ENEMY_ATTACK_MOUTH		4
#define ENEMY_ATTACK_MOUTH_E		5
#define ENEMY_ATTACK_LHAND		6
#define ENEMY_ATTACK_LHAND_E		7
#define ENEMY_ATTACK_WINGS		8
#define ENEMY_ATTACK_WINGS_E		9
#define ENEMY_ATTACK_WINGS_R		10
#define ENEMY_ATTACK_WINGS_R_E		11
#define ENEMY_ATTACK_TURN_L		12

#define ENEMY_ATTACK_TURN_R		14

#define ENEMY_ATTACK_BONE_NUM		16
```

```C++
void ACEnemy_Dragon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FString AnimBPAdderss = "Class'/Game/Enemy/MountainDragon/Blueprint/BP_AnimBP_Dragon.BP_AnimBP_Dragon_C'";
	UClass* tempAnimBP = LoadObject<UClass>(nullptr, *AnimBPAdderss);
	if (!tempAnimBP) return;
	GetMesh()->SetAnimInstanceClass(tempAnimBP);

	BoneNameArr[ENEMY_ATTACK_RHAND		] = FName("MOUNTAIN_DRAGON_-R-Finger12");
	BoneNameArr[ENEMY_ATTACK_RHAND_E	] = FName("MOUNTAIN_DRAGON_-R-Hand");
	BoneNameArr[ENEMY_ATTACK_HEAD		] = FName("");
	BoneNameArr[ENEMY_ATTACK_HEAD_E		] = FName("");
	BoneNameArr[ENEMY_ATTACK_MOUTH		] = FName("MOUNTAIN_DRAGON_-Neck5");
	BoneNameArr[ENEMY_ATTACK_MOUTH_E	] = FName("MOUNTAIN_DRAGON_-Ponytail1");
	BoneNameArr[ENEMY_ATTACK_LHAND		] = FName("MOUNTAIN_DRAGON_-L-Hand");
	BoneNameArr[ENEMY_ATTACK_LHAND_E	] = FName("MOUNTAIN_DRAGON_-L-Finger12");
	BoneNameArr[ENEMY_ATTACK_WINGS		] = FName("");
	BoneNameArr[ENEMY_ATTACK_WINGS_E	] = FName("");
	BoneNameArr[ENEMY_ATTACK_WINGS_R	] = FName("");
	BoneNameArr[ENEMY_ATTACK_WINGS_R_E	] = FName("");

	ArmRadius = 120.f;
	HeadRadius = 80.f;
}
```

몬스터의 Bone은 PCH에 정수형태로 선언해두었습니다.

각 몬스터의 스켈레탈 메시 별로 Bone의 이름이 달라서, TMap객체에 각 몬스터마다 대응하는 Bone이름을 저장하였습니다.

```C++
bool ACEnemyCharacter::AttackHitCheck(int AttackType, float DamageScale)
{
	bool bResult = false;
	TArray<bool> AdditionalResults;
	FVector StartLocation;
	FVector EndLocation;
	float Radius = 0.f;
	FVector Scale = GetActorScale();
	float FScale = (Scale.X + Scale.Y + Scale.Z) / 3;
	switch (AttackType)
	{
	case(ENEMY_ATTACK_RHAND):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_RHAND]);//"R_RowerArm");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_RHAND_E]);//"R_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_HEAD):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_HEAD]);// "Head");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_HEAD_E]);//"Jaw03");
		Radius = HeadRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_LHAND));
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_RHAND));
		break;
	case(ENEMY_ATTACK_MOUTH):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_MOUTH]);//"Head");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_MOUTH_E]);//"Jaw03");
		Radius = HeadRadius * FScale;
		break;
	case(ENEMY_ATTACK_LHAND):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_LHAND]);//"L_LowerArm");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_LHAND_E]);//"L_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_WINGS):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS]);//"WingClaw1_L");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS_E]);//"WingClaw2_L");
		Radius = ArmRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_WINGS_R));
		break;
	case(ENEMY_ATTACK_WINGS_R):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS_R]);//"WingClaw1_R");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS_R_E]);//"WingClaw2_R");
		Radius = ArmRadius * FScale;
		break;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);

	bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(Radius),
		Params
	);

	if (AdditionalResults.Num() > 0)
	{
		for (bool d : AdditionalResults)
		{
			bResult |= d;
		}
	}

	if (bResult)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(HitResult.GetActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
			bResult = PC->HitDamage(AttackDamage * DamageScale, this, HitResult.Location, AttackPower);
		}
	}

	//DrawDebugSphere(GetWorld(), StartLocation, Radius, 32, bResult ? FColor::Green : FColor::Red);
	//DrawDebugSphere(GetWorld(), EndLocation, Radius, 32, bResult ? FColor::Green : FColor::Red);

	return bResult;
}
```

히트 판정 수행 시, 파라미터를 통해 전달받은 Bone의 Index를 통해 히트 판정을 수행할 두 Bone의 위치를 저장합니다.

각 Bone의 위치에 플레이어가 충돌했을 경우 PlayerCharacter의 HitDamage 함수를 호출하여 대미지를 전달합니다.

HitDamage는 대미지 전달 여부를 반환하고, 성공적으로 전달했을 시 true를 반환하도록 구현하였습니다.

```C++
bool ACPlayerCharacter::HitDamage(float e, ACEnemyCharacter* Attacker, FVector HitLocation, int Power)
{
	if (GetState(PLAYER_ROLL_INVINCIBLE))
	{
		if (!GetState(PLAYER_DODGED))
		{
			OnDodgedAttack();
		}
		UE_LOG(LogTemp, Log, TEXT("Player Roll Dodged"));
		return false;
	}
	else if (GetState(PLAYER_RAGDOLL) || GetState(PLAYER_GETTINGUP))
	{
		UE_LOG(LogTemp, Log, TEXT("Player in Ragdoll"));
		return false;
	}
	else if (GetState(PLAYER_ULT_INVINCIBLE))
	{
		UE_LOG(LogTemp, Log, TEXT("Player Using Ult"));
		return false;
	}

	ItemStat CurrStat = ItemStat();

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	if (UIController == nullptr) return false;
	UIController->EquippedItemStat(CurrStat);

	UE_LOG(LogTemp, Log, TEXT("Player Defence = %f"), CurrStat._Defence);
	float DeffencePer = 1 - (CurrStat._Defence / 500.f);
	if (DeffencePer <= 0.1f) DeffencePer = 0.1f;
	UE_LOG(LogTemp, Log, TEXT("Player Defence Damage = %f"), DeffencePer);
	HP -= (e * DeffencePer);
	SetState(PLAYER_UI_INTERACTING, false);
	SetLastDealingEnemy(Attacker);
	
	UIController->AddRecentDamage(e * DeffencePer / MaxHP);


	ShowDamageUI(e * DeffencePer, HitLocation, true);

	if (HP <= 0.f) return true;
	switch (Power)
	{
	case(PLAYER_HIT_REACT_STAND):
		break;
	case(PLAYER_HIT_REACT_FLINCH):
		StopAnimMontage();
		SetState(PLAYER_ATTACKING, true);
		HitReact.ExecuteIfBound();
		break;
	case(PLAYER_HIT_REACT_HITDOWN):
		StopAnimMontage();
		SetState(PLAYER_RAGDOLL, false);
		SetState(PLAYER_CANGETUP, true);
		HitDown.ExecuteIfBound();
		break;
	}
	return true;
}
```

HitDamage 호출 시, 무적 판정 여부를 검사합니다.

PCH에 선언한 ItemStat 구조체를 사용해서 플레이어의 능력치를 불러오고, 플레이어의 방어력을 토대로 대미지를 조정하였습니다.

![image](https://github.com/user-attachments/assets/a4ba96e2-fa9f-4262-a7af-d1fefd7c7cb1)

PlayerController의 인터페이스, UIController를 통해 AddRecentDamage 함수를 호출하고,

체력바에서의 최근에 입은 대미지를 추가하였습니다.

```C++
void UCUserWidget_CircularProgressBar::AddRecentDamage(float Damage)
{
	RecentDamageSum += Damage;
	bEraseRecentDamage = false;
	GetWorld()->GetTimerManager().ClearTimer(RecentDamageTimer);
	GetWorld()->GetTimerManager().SetTimer(RecentDamageTimer, FTimerDelegate::CreateLambda([&] {
		bEraseRecentDamage = true;
		}), 2.f, false
	);
}

void UCUserWidget_CircularProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
	{
	// …생략
	if (bEraseRecentDamage && RecentDamageSum > 0.f)
	{
		RecentDamageSum -= RecentDamageSum * InDeltaTime * 0.6f;
		RecentDamageSum = RecentDamageSum < 0.f ? 0.f : RecentDamageSum;
	}
}
```

최근에 입은 대미지는 Timer를 사용해서 2초 뒤 서서히 사라지는 효과를 구현하였습니다.

```C++
bool ACPlayerCharacter::HitDamage(float e, ACEnemyCharacter* Attacker, FVector HitLocation, int Power)
{
	// …생략
	ShowDamageUI(e * DeffencePer, HitLocation, true);

	if (HP <= 0.f) return true;
	switch (Power)
	{
	case(PLAYER_HIT_REACT_STAND):
		break;
	case(PLAYER_HIT_REACT_FLINCH):
		StopAnimMontage();
		SetState(PLAYER_ATTACKING, true);
		HitReact.ExecuteIfBound();
		break;
	case(PLAYER_HIT_REACT_HITDOWN):
		StopAnimMontage();
		SetState(PLAYER_RAGDOLL, false);
		SetState(PLAYER_CANGETUP, true);
		HitDown.ExecuteIfBound();
		break;
	}
	return true;
}
```

Power 변수를 조정하여 피격 시 플레이어의 리액션을 조정할 수 있도록 구현하였습니다.

FLINCH나 HITDOWN의 경우, 현재 재생 중인 애니메이션을 중단하고 쓰러뜨리거나 움츠리는 애니메이션을 재생하였습니다.

### 2-3-2. Queue를 활용한 대미지 UI 구현

```C++
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

			DamageUI->SetDamage(Damage);
			DamageUI->SetDamageColor(C);
			DamageUI->AddToViewport();
			DamageUI->SetVisibility(ESlateVisibility::Visible);
			DamageUIQueue.Enqueue(DamageUI);
			GetWorld()->GetTimerManager().SetTimer(DamageShowTimer, this, &ACPlayerController::DequeueDamageUI, 1.f);
		}
	}
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
```

피격 또는 타격 시, ShowDamageUI를 통해 대미지 수치를 화면에 표시할 수 있도록 구현하였습니다.

피격과 타격은 IsAttacked 변수를 통해 구분하였습니다.

공격당했을 경우 화면 정중앙에 대미지를 표시하고, 공격을 했을 경우는 ProjectWorldLocationToScreen 함수를 사용해서

히트 이벤트가 발생한 위치에 대미지 UI를 위치시켰습니다.

대미지 UI는 생성 시 Queue에 Push되고, 타이머와 DamageUIQueue를 통해 특정 시간 이후 제거됩니다.

```C++
void UCDamageUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (GetRenderOpacity() <= 0.f) Destruct();
	SetRenderOpacity(GetRenderOpacity() - InDeltaTime);
	FWidgetTransform T = GetRenderTransform();
	FVector2D newLocation = T.Translation + FVector2D(0.f, InDeltaTime*20);
	T.Translation = newLocation;
	SetRenderTransform(T);
}
```

대미지 UI는 NativeTick을 통해 투명해지고, 점점 아래로 이동하도록 구현하였습니다.

![atk_bs_ult](https://github.com/user-attachments/assets/6d278978-2ff6-4b8f-94dd-e4715b540996)

## 2-4. 아이템 드랍 시스템

```C++
void UQuestComponent::Init_Quest9()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));
	if (tempActor == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Dragon::StaticClass());
	if (EC == nullptr) return;

	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Spike.DropTable_Spike"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 4000.f;
	Config._MaxHP = 4000.f;
	Config._AttackDamage *= 2.5f;
	EC->SetMonsterConfig(Config);
}
```

![image](https://github.com/user-attachments/assets/e68b4bb2-0b33-469e-acbe-2e73007ab2fd)

몬스터는 각자 드랍 아이템에 대한 데이터 테이블을 가지고 있고, 스폰 시 지정할 수 있도록 하였습니다.

드랍 테이블은 아이템 코드와 드랍 확률을 저장해두었습니다.


```C++
void ACEnemyCharacter::Die()
{
	if (!bIsDying)
	{
		bIsDying = true;

		if (LastHitCharacter == nullptr) LastHitCharacter = GetDealingPlayer();

		DetachFromControllerPendingDestroy();

		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		SetActorEnableCollision(true);

		IIPlayerQuest* PQ = Cast<IIPlayerQuest>(LastHitCharacter);
		if (PQ != nullptr)
		{
			PQ->MonsterKilledCount(this);
		}

		if (!bIsRagdoll)
		{
			// Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetSimulatePhysics(true);
			GetMesh()->WakeAllRigidBodies();
			GetMesh()->bBlendPhysics = true;

			UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
			if (CharacterComp)
			{
				CharacterComp->StopMovementImmediately();
				CharacterComp->DisableMovement();
				CharacterComp->SetComponentTickEnabled(false);
			}


			GetWorld()->GetTimerManager().SetTimer(DiedClock, FTimerDelegate::CreateLambda(
				[&] {
					if (DiedFXComponent != nullptr) DiedFXComponent->ActivateSystem();
					bVeporizeCorpes = true;
				}
			), 3.f, false );

			

			//SetLifeSpan(28.0f);
			bIsRagdoll = true;

			//Drop Item
			FDropTableRow* R;
			ACDroppedItem* DI;
			AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());

			if (DropTable == nullptr) return;
			for (FName RowName : DropTable->GetRowNames())
			{
				UE_LOG(LogTemp, Log, TEXT("Row Name : %s"), *RowName.ToString());
				R = DropTable->FindRow<FDropTableRow>(RowName, FString(""));
				if (R == nullptr || FMath::RandRange(0.f, 1.f) > R->ItemDropRate) continue;

				UCInventoryItemData* ID = GM->GetItem(FName(R->ItemCode));
				if (ID == nullptr) continue;
				DI = GetWorld()->SpawnActor<ACDroppedItem>(ACDroppedItem::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
				DI->SetPossessingItem(*ID);
			}
		}
	}
}
```

몬스터 사망 시, 몬스터의 드랍 테이블에서 RandRange 함수를 통해 드랍률을 계산하고,

드랍 확률을 충족한다면 아이템 구체를 생성하고, 아이템 정보(UCInventoryItemData)를 저장하도록 하였습니다.

```C++
void ACDroppedItem::BeginPlay()
{
	Super::BeginPlay();
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &ACDroppedItem::OnOverlapBegin);
	//Collider->OnComponentEndOverlap.AddDynamic(this, &ACDroppedItem::OnOverlapEnd);
	
	float vDegree = FMath::RandRange(0.f, 30.f);
	float hDegree = FMath::RandRange(0.f, 359.f);
	float V = FMath::DegreesToRadians(vDegree);
	float H = FMath::DegreesToRadians(hDegree);
	float Power = 2.f;
	
	FVector DirNor = FVector(FMath::Sin(V) * FMath::Cos(H), FMath::Sin(V) * FMath::Sin(H), FMath::Cos(V));
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + DirNor * Power, FColor::Green, false, 10.f);
	//UE_LOG(LogTemp, Log, TEXT("Force Direction %s"), *DirNor.ToString());
	StaticMeshComponent->AddForce(DirNor * Power);
}
```

아이템 구체(ACDroppedItem)은 생성과 동시에 무작위 방향으로 발사되도록 구현하였습니다.

0 - 30도의 수직 방향, 0 - 359도의 수평 방향을 방향벡터로 연산하여 AddForce함수를 사용해 발사하였습니다.

```C++
void ACDroppedItem::CheckSweepCharacter()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);

	if (!PickedUp && (GetWorld()->SweepSingleByObjectType(
		HitResult,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(50.f),
		Params
	)))
	{	// Player Colided
		if (OverlapingPlayerCharacter != nullptr) return;

		OverlapingPlayerCharacter = Cast<ACPlayerCharacter>(HitResult.GetActor());
		if (OverlapingPlayerCharacter == nullptr) return;
		if (ACPlayerController* PCC = Cast<ACPlayerController>(OverlapingPlayerCharacter->GetController()))
		{
			PCC->ShowDroppedItemList(true, this, PossessingItem);
		}
		return;
	}
	if (OverlapingPlayerCharacter != nullptr)
	{
		// Player Dettached
		if (ACPlayerController* PCC = Cast<ACPlayerController>(OverlapingPlayerCharacter->GetController()))
		{
			PCC->ShowDroppedItemList(false, this, PossessingItem);
		}
		OverlapingPlayerCharacter = nullptr;
		return;

	}
}
```

아이템 구체는 매 Tick마다 CheckSweepCharacter 함수를 호출해서 플레이어와의 충돌 여부를 검사힙니다.

초기는 OnOverlap 이벤트에 함수를 바인딩했으나 생성과 동시에 겹치는 경우가 많아 버그를 줄이기 위해 이런 방식을 채택하였습니다.

플레이어와 겹쳐있을 시, PlayerController의 ShowDroppedItemList를 호출해서 현재 가지고 있는 아이템 정보(UCInventoryItemData)를 전달합니다.

```C++
void ACPlayerController::ShowDroppedItemList(bool e, ACDroppedItem* Dropped, UCInventoryItemData* ItemData)
{
	if (Dropped == nullptr) return;
	if (DroppedItemList == nullptr) return;
	if (!IsValid(Dropped) || ItemData == nullptr) return;
	if (e)
	{
		DroppedItemList->SetVisibility(ESlateVisibility::Visible);
		DroppedItemList->ItemList->AddItem(ItemData);
		DroppedItemPtrArr.Add(Dropped);
		PickUpItemInteract_ShowAndInputReady();
	}
	else
	{
		DroppedItemList->ItemList->RemoveItem(ItemData);
		//if (DroppedItemPtrArr.Contains(Dropped)) DroppedItemPtrArr.Remove(Dropped);
		if (DroppedItemList->ItemList->GetNumItems() == 0)
		{
			DroppedItemList->SetVisibility(ESlateVisibility::Hidden);
			DroppedItemPtrArr.Empty();
			NPCInteract_UnShow();
		}
		else
		{
			DroppedItemPtrArr.Remove(Dropped);
		}
	}
}
```

![image](https://github.com/user-attachments/assets/71e4c985-be60-4ff3-96bc-dca8a0bf6a6c)

ShowDroppedItemList의 매개변수 e가 true인 채로 호출되면,

아이템 정보를 DroppedItemList에 추가하고 아이템 구체의 포인터를 배열에 저장합니다.

반대로 플레이어와 겹치지 않을 경우는 e가 false인 채로 호출되어,

DroppedItemList에서 아이템 정보를 제거하고, 아이템 구체의 포인터 또한 제거합니다.

```C++
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
```

또한 아이템 구체와 충돌 중일 때 PickUpItemInteract_ShowAndInputReady함수를 호출해서

상호작용 버튼을 화면에 표시하고, E버튼 클릭 시 아이템 픽업을 수행하도록 SetButtonMode 함수를 통해서 현재 상태를 저장합니다.

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

void ACPlayerController::PickUpItemInteract_Interact()
{
	if (ButtonActionUI == nullptr) return;
	TArray<UObject*> tempArr = DroppedItemList->ItemList->GetListItems();
	//UCInventoryItemData* tempItem;
	//ACDroppedItem* tempDroppedItem;
	for (UObject* temp : tempArr)
	{
		if (!IsValid(temp)) continue;
		UCInventoryItemData* tempItem = Cast<UCInventoryItemData>(temp);
		if (tempItem == nullptr) continue;
		AddInventoryItem(tempItem);
		DroppedItemList->ItemList->RemoveItem(tempItem);
	}
	for (ACDroppedItem* tempDroppedItem : DroppedItemPtrArr)
	{
		if (!IsValid(tempDroppedItem)) continue;
		//tempDroppedItem = Cast<ACDroppedItem>(temp);
		if (tempDroppedItem == nullptr) continue;
		tempDroppedItem->PlayerPickUp();
		//tempDroppedItem->Destroy();
	}
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetCharacter());
	if (PC == nullptr) return;
	PC->PickUp.ExecuteIfBound();
	NPCInteract_UnShow();

	DroppedItemList->SetVisibility(ESlateVisibility::Hidden);
}
```

상호작용 버튼을 통해 PickUpItemInteract_Interact함수가 호출되면,

DroppedItemList에 저장되어 있는 모든 아이템을 [*1-1-1. 아이템 획득*](#1-1-1-아이템-획득)에서 설명한 AddInventoryItem함수를 통해 인벤토리에 추가합니다.

아이템 구체의 포인터가 저장되어 있는 배열을 통해 충돌 중인 모든 아이템 구체를 비활성화합니다.

### 2-4-1. 나이아가라 시스템을 활용한 몬스터 사망 이펙트 구현

```C++
void ACEnemyCharacter::Die()
{
	if (!bIsDying)
	{
		bIsDying = true;

		if (LastHitCharacter == nullptr) LastHitCharacter = GetDealingPlayer();

		DetachFromControllerPendingDestroy();

		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		SetActorEnableCollision(true);

		IIPlayerQuest* PQ = Cast<IIPlayerQuest>(LastHitCharacter);
		if (PQ != nullptr)
		{
			PQ->MonsterKilledCount(this);
		}

		if (!bIsRagdoll)
		{
			// Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetSimulatePhysics(true);
			GetMesh()->WakeAllRigidBodies();
			GetMesh()->bBlendPhysics = true;

			UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
			if (CharacterComp)
			{
				CharacterComp->StopMovementImmediately();
				CharacterComp->DisableMovement();
				CharacterComp->SetComponentTickEnabled(false);
			}


			GetWorld()->GetTimerManager().SetTimer(DiedClock, FTimerDelegate::CreateLambda(
				[&] {
					if (DiedFXComponent != nullptr) DiedFXComponent->ActivateSystem();
					bVeporizeCorpes = true;
				}
			), 3.f, false );

			

			//SetLifeSpan(28.0f);
			bIsRagdoll = true;

			//Drop Item
			FDropTableRow* R;
			ACDroppedItem* DI;
			AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());

			if (DropTable == nullptr) return;
			for (FName RowName : DropTable->GetRowNames())
			{
				UE_LOG(LogTemp, Log, TEXT("Row Name : %s"), *RowName.ToString());
				R = DropTable->FindRow<FDropTableRow>(RowName, FString(""));
				if (R == nullptr || FMath::RandRange(0.f, 1.f) > R->ItemDropRate) continue;

				DI = GetWorld()->SpawnActor<ACDroppedItem>(ACDroppedItem::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
				UCInventoryItemData* ID = GM->GetItem(FName(R->ItemCode));
				if (ID == nullptr) continue;
				DI->SetPossessingItem(*ID);
			}
		}
	}
}
```

```C++
void ACPlayerCharacter::MonsterKilledCount(ACEnemyCharacter* MonsterKilled)
{
	//UE_LOG(LogTemp, Log, TEXT("Killed Monster Class : %s"), MonsterKilled->GetFName());

	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		PC->CheckQuest(MonsterKilled);
		//PC->CheckQuest(this, MonsterClass);
	}
}
```

몬스터 사망 시, [*아이템 획득*](#1-1-1-아이템-획득) 시와 동일하게 CheckQuest 함수를 호출해서 퀘스트 목적 달성 여부를 검사합니다.

또한 SetSimulatePhysics함수를 호출하고, 모든 애니메이션을 정지시켜 랙돌 형태로 전환하여 시체를 구현하였습니다.

```C++
void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ACStageGameMode* StageGM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	if (StageGM != nullptr)
	{
		StageGM->PlayerDodged.BindUFunction(this, "OnPlayerDodged");
		StageGM->PlayerDodgedEnd.BindUFunction(this, "OnPlayerDodgedEnd");
	}

	if (GetMesh() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACEnemyCharacter : Can Not Load Mesh"));
		return;
	}

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyCharacter::OnOverlapPlayer);
	GetMesh()->OnComponentEndOverlap.AddDynamic(this, &ACEnemyCharacter::OnOverlapEndPlayer);

	DiedFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		DiedFX, GetMesh(), FName(), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTargetIncludingScale, true, false
	);

	//MI_D_FullBody = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this, "DynamicInstanceMaterial_MountainDragon");
}
```

![image](https://github.com/user-attachments/assets/244c4023-7969-4b40-ac40-26a62bf9ceee)


몬스터 스폰 시, 나이아가라 시스템(DiedFX)를 Attach하여 몬스터 사망 후 타이머를 통해 활성화하도록 구현하였습니다.

해당 나이아가라 시스템은 SkeletalMeshLocation을 사용해서 Attach되어 있는 스켈레탈 메시의 무작위 위치에서 파티클이 스폰되고,

Gravity Force와 Jitter Position을 적용시켜 흔들리며 공중으로 날아가도록 구현하였습니다.

```C++
void ACEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HP <= 0.f)
	{
		Die();

		if (bVeporizeCorpes && DieGlow < 1.f)
		{
			DieGlow += DeltaTime / 15.f;
			if (DieGlow > 1.f)
			{
				DieGlow = 1.f;
			}

			if (MI_D_FullBody != nullptr)
			{
				MI_D_FullBody->SetScalarParameterValue("CorpseVepor", DieGlow);
			}
			if (DiedFXComponent != nullptr)
			{
				if (DieGlow < 1.f)
				{
					DiedFXComponent->SetFloatParameter("SpawnRate", (1 - DieGlow) * DieGlowSpawnRate);
					DiedFXComponent->SetFloatParameter("SpriteSizeMin", (1 - DieGlow) * 7 + 3);
					DiedFXComponent->SetFloatParameter("SpriteSizeMax", (1 - DieGlow) * 20 + 10);
				}
				if (DieGlow >= 1.f)
				{
					DiedFXComponent->Deactivate();
				}
			}
		}
		return;
	}

	if (OneSecTickInteager < GetWorld()->GetTimeSeconds())
	{
		OneSecTickInteager = GetWorld()->GetTimeSeconds();
		for (auto& AEID : DamagedAttackEventIDMap)
		{
			if (AEID.Value + 3 < OneSecTickInteager) continue;
			DamagedAttackEventIDMap.Remove(AEID.Key);
		}
	}

	//Bone Correction
	//GetMesh();
}
```

사망 이후 Tick함수를 통해 사망 시 나이아가라 시스템의 파라미터를 조정하여 크기가 점진적으로 줄어들며 비활성화되도록 구현하였습니다.

### 2-4-2. 머티리얼을 활용한 몬스터 사망 이펙트 구현

![image](https://github.com/user-attachments/assets/45fa03ac-3eb9-4c0e-a63a-a50ee0868ccc)

몬스터 사망 시, 텍스쳐의 특정 부분을 Desaturation이 적용된 부분으로 교체하여 몬스터가 석화되는 듯한 효과를 구현하였습니다.

RaidialGradient를 사용해서 CorpseVepor 변수에 비례하여 TextureSample을 점점 흑백으로 전환시켰습니다.

```C++
void ACEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HP <= 0.f)
	{
		Die();

		if (bVeporizeCorpes && DieGlow < 1.f)
		{
			DieGlow += DeltaTime / 15.f;
			if (DieGlow > 1.f)
			{
				DieGlow = 1.f;
			}

			if (MI_D_FullBody != nullptr)
			{
				MI_D_FullBody->SetScalarParameterValue("CorpseVepor", DieGlow);
			}
			if (DiedFXComponent != nullptr)
			{
				if (DieGlow < 1.f)
				{
					DiedFXComponent->SetFloatParameter("SpawnRate", (1 - DieGlow) * DieGlowSpawnRate);
					DiedFXComponent->SetFloatParameter("SpriteSizeMin", (1 - DieGlow) * 7 + 3);
					DiedFXComponent->SetFloatParameter("SpriteSizeMax", (1 - DieGlow) * 20 + 10);
				}
				if (DieGlow >= 1.f)
				{
					DiedFXComponent->Deactivate();
				}
			}
		}
		return;
	}

	if (OneSecTickInteager < GetWorld()->GetTimeSeconds())
	{
		OneSecTickInteager = GetWorld()->GetTimeSeconds();
		for (auto& AEID : DamagedAttackEventIDMap)
		{
			if (AEID.Value + 3 < OneSecTickInteager) continue;
			DamagedAttackEventIDMap.Remove(AEID.Key);
		}
	}

	//Bone Correction
	//GetMesh();
}
```

사망 후 Tick에서 CorpseVepor 변수를 점점 증가시켜 사망 이펙트가 종료됨에 따라

캐릭터 메시가 전부 흑백으로 표현되도록 구현하였습니다.

![perish_2](https://github.com/user-attachments/assets/19eb1ee8-5869-4b17-9e2b-06692204d08e)


## 2-5. 공격 시스템

### 2-5-1. 머티리얼을 활용한 무기 이펙트 구현

![image](https://github.com/user-attachments/assets/ad3a63d0-46d3-43b9-b1be-d6db546ac9ae)

Time 변수와 코사인을 사용하여 특정 주기로 크고 작아지는 변수 Clock Circular Opacity와 Clock Opacity Whole을 선언하였습니다.

변수에 비례해서 점멸하는 효과를 구현하였고, Attacking이 1일 경우 주기를 무시하고 강제로 발광합니다.

![image](https://github.com/user-attachments/assets/0ef5ecb1-ea18-4919-ac34-7b472ae30698)

![bs_glowing_part0](https://github.com/user-attachments/assets/c188151b-20c7-4868-9ad8-d2ad15b99395)

RadialGradient를 사용해서 텍스쳐의 특정 지점으로부터 커지고 작아지는 텍스쳐를 구현하였습니다.

![image](https://github.com/user-attachments/assets/baeb1e18-f67b-4c42-bb25-e1470b75be86)

![bs_glowing_part1](https://github.com/user-attachments/assets/dbff4c86-c148-4dc6-b4fc-8cbf5fb5772b)

해당 텍스쳐에 기존의 텍스쳐를 곱해 윤곽선을 강조하는 텍스쳐를 구현하였습니다.

![image](https://github.com/user-attachments/assets/3ccf4138-1922-4604-8e8d-efc025e4c522)

![bs_glowing_part2](https://github.com/user-attachments/assets/9a5b6fb3-b56f-4348-a21a-aefd4972736d)

해당 텍스쳐에 RGB값을 높게 잡은 색상을 곱해 이미시브 컬러로 사용하여 광원효과를 구현하였습니다.

![image](https://github.com/user-attachments/assets/9fb72069-5951-4f4d-aef0-c0043e8f2eba)

![bs_glowing_part3](https://github.com/user-attachments/assets/1ebceb84-9d82-4a49-98b6-e3123920c6b7)

특정 지점으로부터 커지고 작아지는 텍스쳐와 기존 텍스쳐를 이용해

점멸하며 보여질 부분을 구현하여 오파시티로 사용하였습니다.

![bs_glowing_whole](https://github.com/user-attachments/assets/4447d3ef-f0e6-4f32-bbc9-c2fb36d53d28)

### 2-5-2. AnimNotify를 활용한 공격 연계 시스템 구현

![atk_bs_switch](https://github.com/user-attachments/assets/95d1d322-9c63-497d-b827-b6c2fc1b0503)

좌, 우클릭을 연계하여 다양한 공격을 수행할 수 있도록 구현하였습니다.

```C++
void ACPlayerCharacter::LMBTriggered()
{
	SetKeyState(PLAYER_INPUT_LMB, true);

	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			//(this->*LMBPressedPointer)(*this);
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->LMB_Triggered(AR);
			StaminaSpend(AR.StaminaUsed);
		}
	}
}

void ACPlayerCharacter::LMBCompleted()
{
	SetKeyState(PLAYER_INPUT_LMB, false);

	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			//(this->*LMBPressedPointer)(*this);
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->LMB_Completed(AR);
			StaminaSpend(AR.StaminaUsed);
		}
	}
}
```

인터페이스를 정의해 무기마다 서로 다른 행동을 수행하도록 구현하였습니다.

![atk_bs_pyeong](https://github.com/user-attachments/assets/eb82d845-7e74-405c-a9b3-4f69d30499f0)

![image](https://github.com/user-attachments/assets/f549106a-381e-4961-a946-c34beb9552bc)

```C++
void UCAnimNotifyState_PlayerComboWait::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPC(MeshComp))
	{
		PC->SetContinueCombo(false);
		PC->SetState(PLAYER_ATTACK_CANCLE_UNLOCK, false);
	}
}

void UCAnimNotifyState_PlayerComboWait::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (GetPC(MeshComp))
	{
		if (!PC->GetContinueCombo() && !PC->GetState(PLAYER_BS_ESCAPE_COMBO_TAB))
		{
			PC->StopAnimMontage();
			PC->SetState(PLAYER_ATTACKING, false);
		}
	}
}
```

기본 연계 공격은 하나의 애니메이션을 활용해 구현하였습니다.

PlayerComboWait AnimNotifyState를 구현해 해당 애님 노티파이 도중 입력이 없을 경우

애니메이션을 멈추고 공격을 중지하도록 구현하였습니다.

NotifyBegin에서 ContinueCombo 변수를 false로 설정하여 버튼 입력을 받을 준비를 하도록 하였습니다.

```C++
void ACBattleStaff::LMB_Triggered(struct AttackResult& AttackResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;
	float Stamina = 0.f;

	if (BruteMode)
	{
		// …생략
	}
	else
	{
		if (!PC->GetState(PLAYER_ATTACKING) && !PC->GetState(PLAYER_ROLLING) && !PC->GetMovementComponent()->IsFalling())
		{
			PC->SetState(PLAYER_ATTACKING, true);
			PC->MeleeAttackCombo.ExecuteIfBound();

			ActivateEffect();
			RequiredStamina = 6.f;
		}
		if (!PC->GetContinueCombo())
		{
			PC->SetContinueCombo(true);
		}
		if (PC->GetState(PLAYER_COMBO_STACK_2) || PC->GetState(PLAYER_COMBO_STACK_3))
		{
			RequiredStamina = 4.f;
			DamageScale = 0.7f;
		}
		else DamageScale = 0.3f;
	}
}
```

무기의 LMB_Triggered에서는 ContinueCombo가 False일 경우 해당 값을 true로 할당하여 콤보를 지속시켰습니다.

```C++
void UCAnimNotifyState_PlayerComboIn1::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPC(MeshComp))
	{
		ResetComboStack();
		PC->SetState(PLAYER_COMBO_STACK_1, true);
	}
}

void UCAnimNotifyState_PlayerComboIn1::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (GetPC(MeshComp)) ResetComboStack();
}
```

![image](https://github.com/user-attachments/assets/a8ad299e-f791-4764-a893-e580c826dd6a)

콤보가 지속됨에 따라 우클릭 / Tab으로 다른 공격을 수행할 수 있도록 하였습니다.

각 콤보마다 콤보 스택 State를 부여하였고 PlayerConboIn 애님 노티파이가 진행중일 때 우클릭 / Tab을 누를 경우

강력한 공격으로 연계할 수 있도록 구현하였습니다.

```C++
void ACBattleStaff::RMB_Triggered(struct AttackResult& AttackResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;

	if (BruteMode)
	{
		DamageScale = 0.6f;
		if (PC->GetState(PLAYER_ATTACKING)) return;

		if (!PC->GetState(PLAYER_BRUTEMODE_ORAORA))
		{
			ActivateEffect();
			PC->InitiatePunchCombo.Execute();
			WeaponOraEffect_BruteMode->GraspFist(true);
		}
		PC->SetState(PLAYER_BRUTEMODE_ORAORA, true);
		PC->SetState(PLAYER_ATTACKING, true);
	}
	else
	{
		float Stamina = 0.f;

		if (PC->GetState(PLAYER_COMBO_STACK_3))
		{
			ActivateEffect();
			UE_LOG(LogTemp, Log, TEXT("Combo 3 Stack"));
			PC->StopAnimMontage();
			if (PC->FinishAttack.ExecuteIfBound())
			{
				Stamina = 8.f;
				PC->SetState(PLAYER_ATTACKING, true);
				DamageScale = 1.2f;
			}
		}
		else if (PC->GetState(PLAYER_COMBO_STACK_2))
		{
			ActivateEffect();
			UE_LOG(LogTemp, Log, TEXT("Combo 2 Stack"));
			PC->StopAnimMontage();
			if (PC->Combo2Attack.ExecuteIfBound())
			{
				Stamina = 6.f;
				PC->SetContinueCombo(true);
				PC->SetState(PLAYER_ATTACKING, true);
				DamageScale = 0.5f;
			}
		}
		else if (PC->GetState(PLAYER_COMBO_STACK_1))
		{
			ActivateEffect();
			Stamina = 2.f;
			UE_LOG(LogTemp, Log, TEXT("Combo 1 Stack"));
			PC->StopAnimMontage();
			if (PC->Combo1Attack.ExecuteIfBound())
			{
				PC->SetContinueCombo(true);
				PC->SetState(PLAYER_ATTACKING, true);
				DamageScale = 0.2f;
			}
		}
		AttackResult.StaminaUsed = Stamina;
	}
}
```

콤보 스택 State가 활성화된 상태인 경우 (PlayerConboIn 애님 노티파이 도중) 우클릭 시 현재 공격을 중단하고 연계 공격을 수행하도록 하였습니다.

![atk_bs_switch](https://github.com/user-attachments/assets/7dd9c5e1-a846-416c-ac81-03575dee19ea)


```C++
void UCAnimNotifyState_PlayerAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	//if (StopAttack) return;
	if (PC != nullptr)
	{
		if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(PC->WeaponEquipped))
		{
			IWeaponEquipped->MeleeAttackHitCheck(Staff_0_LFist_1_RFist_2, DamageScale);
		}
	}
}
```

![image](https://github.com/user-attachments/assets/5eff7db2-adaf-4498-90e5-0707d8a62601)

공격 판정이 이루어지는 구간은 PlayerAttack 애님 노티파이를 선언하여 구현하였습니다.

매 Tick마다 MeleeAttackHitCheck함수를 호출하여 충돌을 검사합니다.

충돌을 검사할 위치는 정수(Staff_0_LFist_1_RFist_2)에 저장하여 구분하였습니다.

각 공격 별 대미지 상수는 DamageScale로 전달하여 각 공격별로 다른 대미지를 출력할 수 있도록 하였습니다.

```C++
bool ACBattleStaff::MeleeAttackHitCheck(int32 HitMode, float fDamageScale, float _ExplodeRadius)
{
	switch (HitMode)
	{
	case(1):
		return FistHitCheck(true, fDamageScale);
		break;
	case(2):
		return FistHitCheck(false, fDamageScale);
		break;
	case(3):
		if (WeaponOraEffect == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("WeaponOraEffect Can Not Found"));
			return false;
		}
		return StaffHitCheck(WeaponOraEffect->GetWeaponLocation(true), fDamageScale);
		break;
	case(4):
		return ExplodeHitCheck(_ExplodeRadius, fDamageScale);
		break;
	default:
		return StaffHitCheck(FVector::ZeroVector, fDamageScale);
		break;
	}
}
```

각 공격 별로 다른 판정을 수행합니다.

```C++
bool ACBattleStaff::StaffHitCheck(FVector HitLocation, float fDamageScale)
{
	//FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAttachParentActor());
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);

	FTransform FireSocketTransform;
	bool UltAttacking = (HitLocation != FVector::ZeroVector) ? true : false;
	if (HitLocation != FVector::ZeroVector)
	{
		FireSocketTransform.SetLocation(HitLocation);
	}
	else
	{
		if (FireSocket != nullptr) FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);
	}
	TArray<FHitResult> tempResults;
	bool bResult = GetWorld()->SweepMultiByObjectType(
		tempResults,
		FireSocketTransform.GetLocation(),
		FireSocketTransform.GetLocation(),
		FQuat::Identity,
		OQP,
		UltAttacking ? FCollisionShape::MakeSphere(250.f) : FCollisionShape::MakeSphere(30.f),
		Params
	);

	if (bResult)
	{
		for (FHitResult HitResult : tempResults)
		{
			ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
			if (EC == nullptr || TempHitEnemiesArr.Contains(EC)) continue;

			ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetAttachParentActor());
			if (PC == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("AttachParentActor is not ACPlayerCharacter"));
				return false;
			}

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), StaffMeleeHitSoundCue, GetActorLocation());

			UE_LOG(LogTemp, Log, TEXT("Attack Damage : %f, Damage Scale : %f"), AttackDamage, DamageScale);
			PC->DealtDamage(AttackDamage, UltAttacking ? 5.f : fDamageScale, EC);
			EC->HitDamage(AttackDamage * UltAttacking ? 5.f : fDamageScale, *PC, HitResult.Location);
			TempHitEnemiesArr.Add(EC);

			FTransform HitEffectSpawnTransform;
			HitEffectSpawnTransform.SetLocation(HitResult.Location);
			FRotator HitEffectTempRot = FRotationMatrix::MakeFromX(SwingingDirection.GetSafeNormal()).Rotator();
			HitEffectSpawnTransform.SetRotation(FQuat(HitEffectTempRot));
			HitEffectSpawnTransform.SetScale3D(FVector(0.5f, 0.5f, 0.5f));

			if (MaterialManager != nullptr)
			{
				MaterialManager->SpawnParticle(WeaponEffect[E_MELLEWEAPON_ATTACK_HIT], 1.f, HitEffectSpawnTransform.GetLocation());
			}
		}
	}

	return bResult;
}
```

Sweep 판정은 충돌한 모든 몬스터 객체에 대해 대미지를 전달합니다.

TempHitEnemiesArr에 몬스터의 포인터를 저장하여 해당 공격이 마칠 때까지 충돌한 몬스터에게 대미지를 주지 않도록 하였습니다.

```C++
void UCAnimNotifyState_PlayerAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (PC != nullptr)
	{
		if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(PC->WeaponEquipped))
		{
			IWeaponEquipped->OnAttackSwingEnd();
		}
	}
}
```

```C++
void ACBattleStaff::OnAttackSwingEnd()
{
	BruteChargedAD = 0.f;
	TempHitEnemiesArr.Empty();
}
```

공격 판정이 끝날 때(NotifyEnd) TempHitEnemiesArr을 초기화하여 최근에 공격당한 몬스터가 이후 공격에도 피격될 수 있도록 하였습니다.

### 2-5-3. 여러 애니메이션을 사용한 공격 구현

```C++
void ACBattleStaff::Tab_Triggered(AttackResult& AttackResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	if (!BruteMode)
	{
		bool bComboing = PC->GetState(PLAYER_COMBO_STACK_1) || PC->GetState(PLAYER_COMBO_STACK_3);
		bool bComboing2 = PC->GetState(PLAYER_COMBO_STACK_2);
		if (bComboing || bComboing2)
		{
			PC->SetContinueCombo(false);
			PC->SetState(PLAYER_BS_ESCAPE_COMBO_TAB, true);
			PC->StopAnimMontage();
			PC->BattleStaffUlt.Execute(bComboing);
			PC->SetState(PLAYER_ATTACKING, true);
			AttackResult.Succeeded = true;
		}
		else
		{
			if (PC->GetState(PLAYER_ATTACKING) || BruteGauge < 1.f) return;
			//WeaponOraEffect->SetEffectVisibility(false);
			WeaponOraEffect_BruteMode->SetEffectVisibility(true);
			BruteMode = true;
			PC->Sheath.Execute();
			//PC->SwitchBruteMode(true);
		}
	}
	else
	{
		if (!PC->PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK)) return;

		BruteMode = false;
		WeaponOraEffect_BruteMode->SetEffectVisibility(false);
		PC->Draw.Execute();
		//PC->SwitchBruteMode(false);
	}
}
```

```C++
void UCPlayerAnimInstance::BattleStaffUlt(bool bSkip)
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceBattleStaffUlt, "DefaultSlot", 0.25f, 0.25f, 1.f, 1, -1.f, bSkip? 2.5f : 1.6f);
}
```

콤보 도중 Tab을 누를 경우 공격 판정과 동시에 무기의 모드를 변형합니다.

Delegate를 호출할 때 파라미터를 전달하여 특정 콤보 도중에는 공격 애니메이션의 중간부터 공격을 진행하도록 구현하였습니다.

![image](https://github.com/user-attachments/assets/037ec78e-0aac-4af4-b567-ec1e1a10ba28)

![image](https://github.com/user-attachments/assets/c6d6e12f-33af-49ff-8ba3-2be0ee70b1c2)

콤보 도중 다른 애니메이션으로 넘어가거나, 무기를 투척해야 할 때 등 특정 연산이 필요할 때

WeaponCallFunc 함수를 정의하여 사용하였습니다.

```C++
void UCAnimNotify_WeaponCallFunc::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;
	if (WeaponType < 1)
	{
		switch (ToCallFunc)
		{
		case(0):	// Throw Staff Effect Forward
			PlayerState->ThrowStaffEffect();
			break;
		case(1):	// Turn To Brute Mode If Brute Gauge Is Enough ( Check Condition In Function )
			PlayerState->TurnBruteMode();
			break;
		case(2):	// Throw Direct Forward
			PlayerState->Ult_ThrowStaffEffectDirect();
			break;
		case(3):	// Jump Init
			PlayerState->Ult_Jump();
			break;
		case(4):	// Punch Ready
			PlayerState->Ult_PunchInit();
			break;
		case(5):	// Airbone
			PlayerState->Ult_Airbone();
			break;
		case(6):	// Land + Deal Damage
			PlayerState->Ult_Land();
			break;
		case(7):
			PlayerState->Ult_HitGround();
			break;
		case(8):	// Backflip
			PlayerState->Ult_Backflip();
			break;
		case(9):	// Sheath Switch Back Socket
			PlayerState->SwitchBruteMode(true);
			break;
		case(10):	// Draw Switch Hand Socket
			PlayerState->SwitchBruteMode(false);
			break;
		}
	}
	else
	{
		switch (ToCallFunc)
		{
		case(0):	// Switch Hand To Temp (Left) / Spawn + Attach Beacon To RHand
			PlayerState->SwitchWeaponHoldingHand(true);
			PlayerState->SpawnAndGraspBeacon();
			break;
		case(1):	// Throw Beacon To Target;
			PlayerState->ThrowBeacon();
			break;
		case(2):	// Switch Hand To Normal (Right)
			PlayerState->SwitchWeaponHoldingHand(false);
			break;
		default:
			break;
		}
	}
}
```

에디터 상에서 호출할 함수의 Index(ToCallFunc)를 지정하면 애니메이션의 특정 부분에서 함수를 호출하여

무기 투척, 다른 애니메이션으로의 연계 등을 구현하였습니다.

![atk_bs_switch](https://github.com/user-attachments/assets/9d85f0a2-83f8-4655-ae43-08139b2a5208)
![atk_bs_ult](https://github.com/user-attachments/assets/b5300cbc-9416-4de3-8126-df59fb3b9abc)


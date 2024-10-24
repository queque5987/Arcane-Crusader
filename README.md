# Arcane Crusader<br><br>플레이 영상

[![플레이 영상](https://img.youtube.com/vi/-hKQ6otIoGA/0.jpg)](https://youtu.be/-hKQ6otIoGA)<br><br>
*구버전*<br>
[![플레이 영상](https://img.youtube.com/vi/p7fB2LRsM9Y/0.jpg)](https://youtu.be/p7fB2LRsM9Y)

# 0. 목차
- [1. 게임 흐름](#1.-게임-흐름)
- [2. 구현한 기능](#2.-구현한-기능)
  * [2-1. UI](#2-1-ui)
    + [a. 인벤토리](#a.-인벤토리)
    + [b. 퀵슬롯](#b-퀵슬롯)
    + [c. NPC 대화](#c.-NPC---)
    + [d. 퀘스트](#d-퀘스트)
    + [e. 무기 UI](#e-무기-UI)
  * [2-2. 전투 시스템](#2-2-전투-시스템)
    + [a. 플레이어 공격](#a-플레이어-공격)
    + [b. 몬스터 공격](#b-몬스터-공격)
    + [c. 저스트 회피](#c-저스트-회피)
  * [2-3. 무기 디자인](#2-3-무기-디자인)
# 1. 게임 흐름
![MMB_Summary.drawio](https://github.com/queque5987/MMB/blob/master/MMB_Summary.drawio.png?raw=true)

처음 시작 시 튜토리얼 레벨을 거치며,

마을에서 장비를 정비하고 토벌 퀘스트를 받아 전투 스테이지에서 토벌을 진행하는 방식으로 기획하였습니다.

# 2. 구현한 기능
## 2-1. UI

### a. 인벤토리
![인벤토리 예시](https://github.com/queque5987/MMB/blob/master/inventoryImage.png?raw=true)

```C++
void UCInventoryItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = ListItemObject;

	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
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
![Inventory Item 예시](https://github.com/queque5987/MMB/blob/master/ShopItem.png?raw=true)

아이템 데이터는 CInventoryItemData 클래스로 구현되며,

인벤토리, 상점 등 UI에선 InventoryItem, ShopItem, ItemDetail 등 컨테이너에 따라 다양한 UI를 통해 시각화됩니다.


```C++
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
```

모든 UI는 CPlayerController에서 선언하여 접근 가능하도록 구현하였습니다.

인벤토리는 주로 TileView를 사용하여 구현하였습니다.

**아이템 획득**

![아이템 획득](https://github.com/queque5987/MMB/blob/master/DropItem.png?raw=true)

아이템을 획득하는 경우, CPlayerController 클래스를 통해 InventoryItemData를 ItemList에 추가합니다.

```C++
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

	if (ItemData->GetItemType() > 3)
	{
		for (UObject* HasItem : ItemInventory->ItemList->GetListItems())
		{
			UCInventoryItemData* HasItemData = Cast<UCInventoryItemData>(HasItem);
			if (HasItemData->GetstrName() == ItemData->GetstrName())
			{
				HasItemData->SetItemCount(HasItemData->GetItemCount() + ItemData->GetItemCount());
				CheckQuest(ItemData->GetItemClass());
				return;
			}
		}
	}
	ItemInventory->ItemList->AddItem(ItemData);
	CheckQuest(ItemData->GetItemClass());
}
```

**아이템 장착**

![MMB_Summary.drawio](https://github.com/queque5987/MMB/blob/master/MMB_ItemEquip.drawio.png?raw=true)

```C++
void UCInventoryItem::Equip()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(this->GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (!IsValid(ID)) return;


	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(PC->GetController());
	if (PCC == nullptr) return;

	PCC->IsSocketEmpty(ItemType);

	//Spawn and Equip To Character
	if (ItemType == 0)
	{
		AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ID->GetItemClass(), PC->GetActorLocation(), FRotator::ZeroRotator);
		IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor);
		if (isWeapon == nullptr) return;

		isWeapon->SetIsEquiped(true);
		isWeapon->SetWeaponName(FName(ID->GetstrName()));
		isWeapon->SetAttackDamage(ID->GetAttackDamage());
		isWeapon->SetItemStat(ID->GetItemStats());
		isWeapon->SetBulletType(ID->GetBulletType());

		PC->Equip(*spawnedActor);
	}

	//Add To Inventory Widget

	ReleasePutItem();

	if (PCC->EquipItem(ItemType, *ID)) PCC->RemoveInventoryItem(ID);
}
```

CInventory에 구현되어 있는 Button을 더블클릭할 경우 Equip을 실행합니다.

Socket이 비어있는지 확인하고, 비어있지 않다면 해당 장비 아이템을 UnEquip합니다.

무기라면 Actor를 현재 World에 소환하고, CPlayerCharacter에 정의되어 있는 Equip함수를 통해 Socket에 Attach합니다.

```C++
bool ACPlayerController::EquipItem(int ItemType, UCInventoryItemData& ItemData)
{
	if (ItemInventory->EquipItem(ItemType, ItemData))
	{
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetCharacter());
		AActor* EquippedWeapon = nullptr;
		if (PC != nullptr) EquippedWeapon = PC->GetWeaponEquipped();
		if (EquippedWeapon != nullptr)
		{
			IIWeapon* IEW = Cast<IIWeapon>(EquippedWeapon);
			if (IEW != nullptr)
			{
				EquippedItemStat(*CurrentItemStat);
				IEW->SetItemStat(CurrentItemStat);
			}
		}
		RemoveInventoryItem(&ItemData);
		return true;
	}
	return false;
}
```

CPlayerController에 장착할 아이템 정보가 담긴 CInventoryItemData와 ItemType을 전달합니다.

CInventory를 통해 CInventoryItemData를 ItemType에 맞춰 장비칸에 추가합니다.

무기가 있을 경우 무기 인터페이스를 통해 갱신된 캐릭터의 스탯을 무기에 저장합니다.

장비칸에 추가가 완료되었을 경우 마지막으로 인벤토리에서 해당 아이템을 제외합니다.

### b. 퀵슬롯

![HUD 예시](https://github.com/queque5987/MMB/blob/master/hudInGame.png?raw=true)

![DragIn 상태 Image](https://github.com/queque5987/MMB/blob/master/draginInGame.png?raw=true)

퀵슬롯은 CInventoryItem을 DragIn하는 상태에서 퀵슬롯 버튼을 클릭할 경우 등록이 가능합니다.

```C++
void ACPlayerController::DragInItem(UCInventoryItemData* ToDragItem)
{
	DragOutItem();

	IIItemManager* GM = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (GM == nullptr) return;
	UTexture2D* T = GM->IconGetter(ToDragItem->GetIconTexture());
	if (T == nullptr) return;
	DraggingItem->ItemImage->SetBrushFromTexture(T);

	DraggingItem->AddToViewport();
	UE_LOG(LogTemp, Log, TEXT("Adding Viewport"));
	DraggingItem->SetVisibility(ESlateVisibility::HitTestInvisible);
	DraggingItemDat = ToDragItem;
}
```

CInventoryItem의 Button을 클릭할 경우 CPlayerController의 DragInItem 함수를 실행합니다.

Hidden상태로 존재하는 DraggingItem Widget을 HitTestInvisible 상태로 변경하고,

DraggingItemDat에 Draggin 중인 CInventoryItemData의 포인터를 저장합니다.

그리고, CInventoryItem은 매 Tick마다 MousePointer의 위치를 계산하여 DraggingItem Widget의 Transform을 조정합니다.

```C++
void UCUserWidgetPlayerHUD::OnClickQuickSlot1()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot1Item = UIController->GetQuickSlot();
	
	QuickSlot_1_Tile->ClearListItems();
	if (QuickSlot1Item != nullptr) QuickSlot_1_Tile->AddItem(QuickSlot1Item);
}
```

QuickSlot 클릭 시, DraggingItemDat(GetQuickSlot())을 가져오고, QuickSlot에 추가합니다.

```C++
void ACPlayerCharacter::Quick1()
{
	if (!PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK) || GetState(PLAYER_ATTACKING)) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	int32 ReactAnim = UIController->UseItem(1);
	ItemUsageAction(ReactAnim);
	UE_LOG(LogTemp, Log, TEXT("QuickSlot 1 : Item Type %d"), ReactAnim);
}
```

```C++
int32 ACPlayerController::UseItem(int32 QuickSlotNum)
{
	int32 rtn = -1;
	UCInventoryItemData* ID = nullptr;
	FString QuickSlotItemName = HUDOverlay->GetItemDataOnQuickSlot(QuickSlotNum);
	TArray<UObject*> InventoryItemsArr = ItemInventory->ItemList->GetListItems();
	TArray<UUserWidget*> InventoryItemWidgetsArr = ItemInventory->ItemList->GetDisplayedEntryWidgets();
	for (int i = 0; i < InventoryItemsArr.Num(); i++)
	{
		ID = Cast<UCInventoryItemData>(InventoryItemsArr[i]);
		if (ID == nullptr) continue;
		if (ID->GetstrName() == QuickSlotItemName) // Find QuickSlot Item In Inventory
		{
			int32 CurrCount = ID->GetItemCount();
			ID->SetItemCount(--CurrCount);
			rtn = ID->GetItemType();
			ItemStat* Stat = ID->GetItemStats();
			IIPlayerState* tempState = Cast<IIPlayerState>(GetCharacter());
			if (rtn == ITEM_TYPE_POTION && (Stat != nullptr && PlayerState != nullptr))
			{
				tempState->Heal(Stat->_HealPoint);
			}
			if (CurrCount <= 0)
			{
				RemoveInventoryItem(ID);
			}
		}
	}
	ItemInventory->ItemList->RequestRefresh();
	return rtn;
}
```

QuickSlot에 해당하는 키보드 입력 감지 시, Quickslot에 저장되어 있는 아이템의 CInventoryItemData를 Get하고,

포션일 경우 체력 회복을 실행합니다.

그리고, 아이템 개수를 감소시키고, 0 되었을 경우 Cinventory의 ItemList에서 제거합니다.

### c. NPC 대화
![NPC Conversation](https://github.com/queque5987/Arcane-Crusader/blob/master/MMB_Dialogue.drawio.png?raw=true)

![NPC 대화창 예시](https://github.com/queque5987/MMB/blob/master/NPCConversation.png?raw=true)

NPC와의 대화는 NPC마다 보유하고 있는 DataTable을 통해 진행됩니다.

![NPC DataTable](https://github.com/queque5987/MMB/blob/master/NPCDataTable.png?raw=true)

DataTable은 버튼마다 이동해야 할 Row의 Index를 보유합니다.

BUTTON NEXT POSTLINE = 13일 경우 NextBtn을 클릭 시, NextBtn에 Bind되어 있는 함수를 실행한 후

CNPCConversation Widget의 NPCName, NPCLine을 RowName 213의 NPCName, NPCDialogue로 변경하며,

모든 버튼을 순회하여 버튼 Collum이 -1 이하일 경우 비활성화하는 방식으로 구현하였습니다.

버튼 Collum은 클래스 내부 변수에 저장되어 각 버튼 클릭 시 이동할 Row의 Index를 저장합니다.

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

		// Set Accept Button To Work As Teleport Button Or Quest Accept
		IsQuest_NotTeleport = (BUTTON_QUEST_POSTLINE >= 0) ? true : false;
	}
}
```

위 함수는 NPCConversation UI의 대화 내용을 불러오고, 각 버튼의 활성 여부를 결정하는 함수입니다.

Button 클릭 시 각 버튼의 Pressed Event에 Bind 되어 있는 함수가 실행되며, 위 SetLineFromDialogues 함수를 호출합니다.

### d. 퀘스트

![퀘스트 인게임 예시](https://github.com/queque5987/MMB/blob/master/quest.png?raw=true)

퀘스트는 CQuestData 객체에 퀘스트 목표, 보상 아이템, 요약 등을 저장하도록 구현하였습니다.

퀘스트의 목표는 Class 형태로 저장하며, CEnemyCharacter를 상속할 경우 처치, IWeapon 인터페이스를 상속할 경우 획득 조건으로 인식합니다.

```C++
bool UCQuest::RefreshQuestRecap(UObject* AchievedObject)
{
	FString Recap = QuestRecapString + "\n";
	int Achieved = RequiredClasses.Num();
	for (int i = 0; i < RequiredClasses.Num(); i++)
	{
		if (AchievedObject != nullptr)
		{
			if (AchievedObject->IsA(RequiredClasses[i]))
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

몬스터 처치, 아이템을 획득할 때마다 RefreschQuestRecap()함수를 실행하여 CQuest Widget에 표시될 퀘스트 요약 내용을 업데이트합니다.

또한, 클리어 여부도 검사하여 요구 조건을 충족 시 Widget의 색을 변경하고, 클리어 여부를 리턴합니다. 

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

		ID->SetDetails(ContainingQuest);
		QuestList->AddItem(ID);
	}

	//Battle Stage Quest
	TArray<UCQuestData*> OutArr;
	UIController->HoxyPossessClearableQuest(NPC, OutArr);
	for (UCQuestData* ClearableQuest : OutArr)
	{
		QuestList->AddItem(ClearableQuest);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *ClearableQuest->GetQuestName());
	}


	QuestList->RequestRefresh();
	//Change Quest List Color
	for (UUserWidget* W : QuestList->GetDisplayedEntryWidgets())
	{
		UCListedQuest* ListedQuestWidget = Cast<UCListedQuest>(W);
		if (ListedQuestWidget == nullptr) continue;
		ListedQuestWidget->ResumeButtonStyle();
	}
}
```

NPC와 대화하며 수락 또는 완료 가능한 퀘스트를 불러올 때는 위 함수를 사용합니다.

NPC가 가지고 있는 퀘스트를 검사하고 Quest List에 추가하며,

Player가 가지고 있는 퀘스트 중 상호작용 중인 NPC에게 클리어 가능한 퀘스트를 Quest List에 추가합니다.

추가된 퀘스트 들의 상태를 검사하는 for 루프를 통해 Button들의 색을 회색, 흰색, 황색, 녹색으로 변경하여 클리어, 수락 가능 여부를 표시하였습니다.

### e. 무기 UI

https://youtu.be/BgOAbAdi8f0?si=Hpja779f4S3Am2vm

https://wdnote.tistory.com/211

Rifle Staff의 하단 UI를 포함한 대부분의 머티리얼 UI는 위 링크들을 참고하여 제작하였습니다.

LinearGradient를 통해 원형의 Progress Bar를 만드는 것을 응용하여 원형의 조준점, 리볼버 형태의 무기 선택 UI 등을 구현하였습니다.

우선, **Float** Clock 값에 따라 정가운데를 중심으로 회전하는 Texcoord를 구현하였습니다.

![image](https://github.com/user-attachments/assets/b6882fc6-145d-47d4-8b29-c3f502e4892d)

![image](https://github.com/user-attachments/assets/0476daee-0465-4bf7-9858-03b6de2f6c92) 
![image](https://github.com/user-attachments/assets/b0f57b3b-775e-4562-a0bb-1e359b9d09bd) 

*좌 Clock = 0.f 우 Clock = 0.2f*

![image](https://github.com/user-attachments/assets/d1ce824d-4727-4c13-abaf-bd0b62f27d13)

![image](https://github.com/user-attachments/assets/f15afc62-d10d-4103-9ba6-407a26ba53b8)
![image](https://github.com/user-attachments/assets/054333e9-cb32-4f3e-8be2-472d1d83818d)

*좌 Clock = 0.f 우 Clock = 0.2f*

해당 Texcoord를 사용하여 특정 좌표에 RadialGradient 노드를 통해 생성한 원형의 Texture와

리볼버 형태의 Texture를 위치시켰으며, Clock 값에 따라 원점을 중심으로 회전하도록 하였습니다.

![image](https://github.com/user-attachments/assets/c17f84e9-76d3-4f40-bf51-a3896b67f80a)

각 원은 동일한 함수를 사용하나, Clock 값에 일정 수치를 더하여 회전 각도의 차이를 벌려주었습니다.

RadialGradient와 적절한 Texture들을 곱하여 아래와 같은 형태의 UI를 구현하였습니다.

![image](https://github.com/user-attachments/assets/0565dbae-a082-47ea-b306-d3880fa3e81e)
![image](https://github.com/user-attachments/assets/6b1bddb6-f566-499b-9a40-27899062e035)

![image](https://github.com/user-attachments/assets/cfc5ba98-da43-4b8a-b681-e31289d90970)
![image](https://github.com/user-attachments/assets/35ca1a91-3811-495a-827e-a966c4b585aa)


```C++
void UCUserWidgetPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//...
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
			UE_LOG(LogTemp, Log, TEXT("CylinderAngle : %f"), CylinderAngle);
			RifleSelectMaterial->SetScalarParameterValue("Clock", CylinderAngle);
		}
	}
	//...
}
```

Tab을 입력 받은 뒤 BarrelRollLeft 변수에 2를 대입하여 위 Tick 함수 내 기능을 실행합니다.

결과적으로 자연스럽게 우측으로 회전한 뒤, 좌측으로 다시 돌아오는 UI 애니메이션을 구현하였습니다.

**예시**

[![플레이 영상](https://img.youtube.com/vi/-hKQ6otIoGA/0.jpg)](https://youtu.be/-hKQ6otIoGA?si=Eu4lNhP0UEvp1vbK&t=306)

## 2-2. 전투 시스템
### a. 플레이어 공격

![Player 공격](https://github.com/queque5987/MMB/blob/master/playerattackInGame.gif?raw=true)

```C++
bool ACBattleStaff::MeleeAttackHitCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAttachParentActor());
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);
	FTransform FireSocketTransform;
	if (FireSocket != nullptr) FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);

	bool bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		FireSocketTransform.GetLocation(),
		FireSocketTransform.GetLocation(),
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(30.f),
		Params
	);

	if (bResult)
	{
		ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
		if (EC == nullptr) return false;
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetAttachParentActor());
		if (PC == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("AttachParentActor is not ACPlayerCharacter"));
			return false;
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), StaffMeleeHitSoundCue, GetActorLocation());

		UE_LOG(LogTemp, Log, TEXT("Attack Damage : %f, Damage Scale : %f"), AttackDamage, DamageScale);

		EC->HitDamage(AttackDamage * DamageScale, *PC, HitResult.Location);

		FTransform HitEffectSpawnTransform;
		HitEffectSpawnTransform.SetLocation(HitResult.Location);
		FRotator HitEffectTempRot = FRotationMatrix::MakeFromX(SwingingDirection.GetSafeNormal()).Rotator();
		HitEffectSpawnTransform.SetRotation(FQuat(HitEffectTempRot));
		HitEffectSpawnTransform.SetScale3D(FVector(0.5f, 0.5f, 0.5f));

		UParticleSystemComponent* tempParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_MELLEWEAPON_ATTACK_HIT], HitEffectSpawnTransform);
		if (tempParticle != nullptr)
		{
			HitParticleQueue.Enqueue(tempParticle);
			GetWorld()->GetTimerManager().SetTimer(EffectSpawnTimerHandler, this, &ACBattleStaff::DequeueHitParticle, 0.5f);
		}
	}

	return bResult;
}
```

타격 판정은 공격 애니메이션이 진행되는 도중 Notify State에서 매 Tick마다 MeleeAttackHitCheck가 true를 반환할 때까지 호출하도록 구현하였습니다.

스태프의 Skeletal Mesh에 추가한 FireSocket의 Transform을 기준으로 충돌하는 CEnemyCharacter를 상속하는 객체를 검사합니다.

충돌했다면 SoundCue 재생, 대미지 전달, 타격 이펙트 재생을 수행합니다.

타격 이펙트의 경우는 Queue에 추가하고, Timer를 설정하여 일정 간격 이후에 Destroy합니다.

### b. 몬스터 공격

![Enemy 공격](https://github.com/queque5987/MMB/blob/master/EnemyAttackInGame.gif?raw=true)
![Spike 지상공격](https://github.com/queque5987/MMB/blob/master/SpikeGroundFireInGame.gif?raw=true)
![Spike 공중공격](https://github.com/queque5987/MMB/blob/master/SpikeFlyFireInGame.gif?raw=true)
```C++
bool ACEnemyCharacter::AttackHitCheck(int AttackType)
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
		StartLocation = GetMesh()->GetBoneLocation("R_RowerArm");
		EndLocation = GetMesh()->GetBoneLocation("R_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_HEAD):
		StartLocation = GetMesh()->GetBoneLocation("Head");
		EndLocation = GetMesh()->GetBoneLocation("Jaw03");
		Radius = HeadRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_LHAND));
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_RHAND));
		break;
	case(ENEMY_ATTACK_MOUTH):
		StartLocation = GetMesh()->GetBoneLocation("Head");
		EndLocation = GetMesh()->GetBoneLocation("Jaw03");
		Radius = HeadRadius * FScale;
		break;
	case(ENEMY_ATTACK_LHAND):
		StartLocation = GetMesh()->GetBoneLocation("L_LowerArm");
		EndLocation = GetMesh()->GetBoneLocation("L_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_WINGS):
		StartLocation = GetMesh()->GetBoneLocation("WingClaw1_L");
		EndLocation = GetMesh()->GetBoneLocation("WingClaw2_L");
		Radius = WingClawRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_WINGS_R));
		break;
	case(ENEMY_ATTACK_WINGS_R):
		StartLocation = GetMesh()->GetBoneLocation("WingClaw1_R");
		EndLocation = GetMesh()->GetBoneLocation("WingClaw2_R");
		Radius = WingClawRadius * FScale;
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
			PC->HitDamage(AttackDamage * DamageScale, this, HitResult.Location, AttackPower);
		}
	}
	return bResult;
}
```

몬스터의 근접 공격 판정은 플레이어의 타격 판정과 동일한 방식으로 구현하였습니다.

PCH.h에 정의되어 있는 공격 타입에 따라 피격 범위를 탐지할 SkeletalMesh의 BoneLocation을 달리하여 검사하였습니다.

ENEMY_ATTACK_HEAD 같은 경우는 좌 우 앞발에도 피격 범위를 감지하도록 Reculsive하게 구현하였습니다.

플레이어의 Character는 대미지를 받고 AttackPower에 따라서 움찔하거나 넘어지는 반응을 하게 구현하였습니다.

```C++
void UCAnimNotifyState_EnemyAtk_Fire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!ContinueAttack) return;
	if (MeshComp == nullptr) return;
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(MeshComp->GetOwner());
	if (EC == nullptr) return;
	IIFlyMonster* IEC = Cast<IIFlyMonster>(EC);
	if (IEC == nullptr) return;
	bool IsFlying = IEC->GetIsFlying();
	float projscale = IsFlying ? 30.f : 30.f;
	float projspeed = IsFlying ? 35.f : 25.f;
	float projclock = IsFlying ? 1.4f : 0.65f;
	float projscaleA = IsFlying ? 0.09f : 0.11f;

	FVector JawLocation = MeshComp->GetBoneLocation("Jaw1");
	FVector HeadLocation = MeshComp->GetBoneLocation("Head");

	FVector JawToHead = (JawLocation - HeadLocation).GetSafeNormal();
	FRotator HeadRotation = FRotationMatrix::MakeFromX(JawToHead).Rotator();

	ACProjectile* Proj = MeshComp->GetWorld()->SpawnActor<ACProjectile>(
		ACProjectile::StaticClass(), JawLocation, HeadRotation);

	Proj->SetLaunch(
		EC,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		0.5f,
		1500.f,
		projspeed,
		projclock,
		nullptr,
		false,
		false,
		true,
		projscaleA
	);
	Proj->SetProjCollisionScale(projscale);


	UParticleSystemComponent* FEC = UGameplayStatics::SpawnEmitterAttached(
		FireEffect,
		MeshComp,
		"Jaw1",
		IsFlying ? FVector(80.f, -120.f, 0.f) : FVector(40.f, -60.f, 0.f),
		IsFlying ? FRotator(-90.f, 0.f, -50.f) : FRotator(-90.f, 0.f, -20.f),
		IsFlying ? FVector(3.f, 3.f, 4.f) : FVector(2.5f, 2.f, 2.f),
		EAttachLocation::KeepRelativeOffset,
		true
	);

	FEQueue.Enqueue(FEC);

	FTimerManager& TM = MeshComp->GetWorld()->GetTimerManager();
	TM.SetTimer(AttackTimerHandle, this, &UCAnimNotifyState_EnemyAtk_Fire::FEOff, 0.8f);
}
```

브레스 공격의 경우 Character의 충돌을 감지하는 CProjectile 객체를 매 Tick마다 발사하는 식으로 구현하였습니다.

CProjectile은 투명한 형태로 소환되어 충돌만 감지합니다.

Skeletal Mesh의 Jaw1에 Attach된 Emitter를 지속적으로 소환하고, Queue에 추가하여 타이머를 통해 임의의 시간 이후 Destroy되게 구현하였습니다.

### c. 저스트 회피

https://youtu.be/9_39Wyo-uho?si=aO9v2rGrUoske_FD

위 유튜브를 참고하여 제작하였습니다.

![image](https://github.com/user-attachments/assets/7cac7b29-a396-4672-93e5-83ea3724343c)
![image](https://github.com/user-attachments/assets/6b8b76e9-4679-4f30-b23c-4fc8bd8e808e)

저스트 회피 시의 환경은 Desaturate 노드를 통해 만든 세피아 톤의 Texture와

상하좌우 픽셀의 Scene Depth 차이를 통해 만든 외곽선이 강조된 Texture를 더하여 구현하였습니다.

![image](https://github.com/user-attachments/assets/d5124aa1-b830-4c30-95ad-4e8a614f7565)

그리고 플레이어의 위치와의 거리를 Radius 값으로 빼 구 형태의 Mask를 구현하였고,

Lerp 노드를 통해 저스트 회피 환경과 아닌 환경을 구분하였습니다.

![image](https://github.com/user-attachments/assets/84a77852-cbbd-4e57-8f31-9561f71d0732)
![image](https://github.com/user-attachments/assets/bd6678af-3e57-40f5-bda7-0102b8e04799)

플레이어의 위치는 매 Tick마다 갱신합니다.

```C++
void ACEnemyCharacter::OnPlayerDodged()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (AnimInst == nullptr) return;
	AnimInst->Montage_SetPlayRate(GetCurrentMontage(), 0.2f);
}
```

```C++
void UCEnemyAnimInstance::NativeInitializeAnimation()
{
	// ...
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
저스트 회피 시, 게임모드 클래스를 통해 Delegate를 호출합니다.

해당 Delegate는 Character 클래스와 Animinstance 클래스를 오버라이드하는 클래스에서

현재 재생중인 몬티지와 앞으로 재생 될 몬티지의 재생 속도를 조절합니다.


결과적으로 저스트 회피 시, Radius 값을 감소시켜 멀리서부터 흑백효과가 다가오면서

플레이어를 제외한 몬스터가 느려지는 효과를 구현하였습니다.

![justevade](https://github.com/user-attachments/assets/a8b9b675-13f3-4398-be97-4a19198ef90a)

## 2-3. 무기 디자인
### a. 플레이어 공격

무기의 원래 디자인

![image](https://github.com/user-attachments/assets/c369ca57-3635-48b5-b2b3-d0d0391a84c2)

무기의 머티리얼의 블렌드 모드를 Translucent로 변환하여 투명해지도록 하였습니다.

Desaturate 노드를 통해 BaseColor를 통해 음영을 만들고, Lerp 노드를 통해 색을 곱하였습니다.

RGB 값을 증폭시켜 아래와 같이 빛나는 형태를 구현하였습니다.

![image](https://github.com/user-attachments/assets/5cf6c4e9-7378-408c-a34e-00213074d776)

흑백으로 변한 BaseColor를 토대로 Opacity에 연결할 Texture를 구현하였습니다.

![image](https://github.com/user-attachments/assets/89dec746-b841-4e57-9886-bc152d81b040)

해당 Texture에 RadialGradient를 곱하여 원형으로 변형시킬 수 있도록 하였습니다.

![hammer_opacity](https://github.com/user-attachments/assets/91cc8768-53fb-4e1c-80bc-5bb277ad1355)<br>*Opacity 노드에 연결 될 Texture*

결과적으로 Clock 값에 따라서 Opacity를 변화시키고, 무기가 숨쉬듯 결을 따라 빛나도록 구현하였습니다.

![hammer](https://github.com/user-attachments/assets/d2ff2ee6-79f3-4640-81ec-42a01c19736d)

해당 Mesh는 무기 Actor에 Attach하고, 머티리얼 인스턴스의 파라미터 값을 조정하며 무기와 상호작용하도록 하였습니다.

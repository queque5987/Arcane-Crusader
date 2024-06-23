# 0. 목차
- [1. 기본 구성](#1------)
  * [1-1. UI](#1-1-ui)
    + [a. HUD](#a-hud)
    + [b. 인벤토리](#b-----)
    + [c. NPC 대화](#c-npc---)
    + [d. 퀘스트](#d----)
  * [1-2. 전투](#1-2---)
    + [a. 플레이어](#a-----)
    + [b. 무기](#b---)
    + [c. 몬스터](#c----)

# 1. 게임 흐름
![플로우 차트 요약]()

처음 시작 시 튜토리얼 레벨을 거치며,

마을에서 장비를 정비하고 토벌 퀘스트를 받아 전투 스테이지에서 토벌을 진행하는 방식으로 기획하였습니다.

# 2. 구현한 기능
## 2-1. UI

### a. 인벤토리
![인벤토리 예시]()

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
![Inventory Item 예시]()

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

![MMB_Summary.drawio]()

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

### b. HUD
![HUD 예시]()

**퀵슬롯**
![DragIn 상태 Image]()

퀵슬롯은 CInventoryItem을 DragIn하는 상태에서 퀵슬롯 버튼을 클릭할 경우 등록이 가능합니다.

![DragIn FlowChart]()

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

그리고, 아이템 개수를 감소시키고, 0일 경우 Cinventory의 ItemList에서 제거합니다.

### c. NPC 대화



### d. 퀘스트

## 2-2. 전투
### a. 플레이어
### b. 무기
### c. 몬스터

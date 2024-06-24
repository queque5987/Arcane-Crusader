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

그리고, 아이템 개수를 감소시키고, 0 되었을 경우 Cinventory의 ItemList에서 제거합니다.

### c. NPC 대화

![NPC 대화창 예시]()

NPC와의 대화는 NPC마다 보유하고 있는 DataTable을 통해 진행됩니다.

![NPC DataTable]()

DataTable은 버튼마다 이동해야 할 Row의 Index를 보유합니다.

BUTTON NEXT POSTLINE = 13일 경우 NEXT Button 클릭 시,

RowName 213의 NPCDialogue를 출력 및 버튼 Collum이 -1 이하일 경우 비활성화하는 방식으로 구현하였습니다.

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

![퀘스트 인게임 예시]()

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

## 2-2. 전투
### a. 공격

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

### b. 몬스터

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

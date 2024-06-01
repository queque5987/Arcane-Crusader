// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventoryItem.h"
#include "CPlayerCharacter.h"
#include "CWeapon.h"
#include "IWeapon.h"
#include "IPlayerUIController.h"
#include "IPlayerState.h"
#include "IItemManager.h"
#include "GenericPlatform/GenericPlatformTime.h"

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

		//ItemName->SetText(FText::FromString(ID->GetstrName()));
		if (ID->GetItemType() >= 3)
		{
			ItemQuantity->SetText(FText::FromString(FString::FromInt(ID->GetItemCount())));
		}
		ItemType = ID->GetItemType();
	}
}

void UCInventoryItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton->OnClicked.AddDynamic(this, &UCInventoryItem::OnButtonClicked);
	ItemButton->OnHovered.AddDynamic(this, &UCInventoryItem::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UCInventoryItem::OnUnHovered);
	ClickedSec = 0.f;
}

void UCInventoryItem::Equip()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(this->GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (!IsValid(ID)) return;

	if (ItemType == 0)
	{
		AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ID->GetItemClass(), PC->GetActorLocation(), FRotator::ZeroRotator);
		IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor);
		if (isWeapon == nullptr) return;

		isWeapon->SetIsEquiped(true);
		isWeapon->SetWeaponName(FName(ID->GetstrName()));
		isWeapon->SetAttackDamage(ID->GetAttackDamage());

		PC->Equip(*spawnedActor);
	}

	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(PC->GetController());

	if (PCC == nullptr) return;
	if (PCC->EquipItem(ItemType, *ID)) PCC->RemoveInventoryItem(ID);
}

void UCInventoryItem::UnEquip(FString EquippedSpace)
{
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (!IsValid(ID)) return;
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (PCC == nullptr) return;
	if (PCC->RemoveEquippedItem(EquippedSpace, ID)) PCC->AddInventoryItem(ID);
}

void UCInventoryItem::OnButtonClicked()
{
	if (FPlatformTime::Seconds() - ClickedSec <= 0.35f)
	{
		FString ListViewName;
		GetOwningListView()->GetName(ListViewName);
		if (ListViewName == "ItemList") Equip();
		else UnEquip(ListViewName);

	}
	ClickedSec = FPlatformTime::Seconds();
}

void UCInventoryItem::OnHovered()
{
	UE_LOG(LogTemp, Log, TEXT("CInventoryItem : OnHovered"));

	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	if (PlayerState != nullptr)
	{
		GetOwningPlayer()->GetWorld()->GetTimerManager().ClearTimer(UnHoverTimerHandler);
		PlayerState->SetState(PLAYER_INVENTORY_HOVERRING, true);
		PlayerState->SetHoverringUI(this);
	}

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController != nullptr)
	{
		UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
		if (ID == nullptr) return;
		UIController->ShowItemDetailUI(ID);
	}
}

void UCInventoryItem::OnUnHovered()
{
	UE_LOG(LogTemp, Log, TEXT("CInventoryItem : OnUnHovered"));

	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	if (PlayerState != nullptr)
	{
		PlayerState->SetState(PLAYER_INVENTORY_HOVERRING, false);

		//IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
		//if (PlayerState == nullptr || PlayerState->GetState(PLAYER_INVENTORY_HOVERRING)) return;
		PlayerState->SetHoverringUI(nullptr);

		//GetOwningPlayer()->GetWorld()->GetTimerManager().SetTimer(UnHoverTimerHandler, FTimerDelegate::CreateLambda([&]() {
			//IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
			//if (PlayerState == nullptr || PlayerState->GetState(PLAYER_INVENTORY_HOVERRING)) return;
			//PlayerState->SetHoverringUI(nullptr);
			//}), 0.5f, false
		//);
	}


	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	UIController->UnShowItemDetailUI();
}

void UCInventoryItem::OnRightClicked()
{
	//IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	//IIPlayerState* PC = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	//UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	//if ((PCC == nullptr || ID == nullptr) || !PCC->IsOnShop()) return;
	//int ItemPrice = ID->GetPrice();
	//PCC->RemoveInventoryItem(ID);
	//PCC->ResumeShopInventoryItems();
	//PC->GainPlayerGold(ItemPrice);

	FString ListViewName;
	GetOwningListView()->GetName(ListViewName);
	if (ListViewName == "ItemList") Equip();
	else UnEquip(ListViewName);

	//Equip();
}

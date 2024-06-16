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
	//InventoryOpenedEvent
}

void UCInventoryItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton->OnClicked.AddDynamic(this, &UCInventoryItem::OnButtonClicked);
	ItemButton->OnHovered.AddDynamic(this, &UCInventoryItem::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UCInventoryItem::OnUnHovered);
	//ItemButton->OnPressed.AddDynamic(this, &UCInventoryItem::OnButtonPressed);
	//ItemButton->OnReleased.AddDynamic(this, &UCInventoryItem::OnButtonReleased);
	ClickedSec = 0.f;
}

void UCInventoryItem::Equip()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(this->GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (!IsValid(ID)) return;


	//Spawn and Equip To Character
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

	//Add To Inventory Widget
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(PC->GetController());
	if (PCC == nullptr) return;

	//SwitchbPicked(true, false);
	ReleasePutItem();

	PCC->IsSocketEmpty(ItemType);
	if (PCC->EquipItem(ItemType, *ID)) PCC->RemoveInventoryItem(ID);

}

void UCInventoryItem::UnEquip(FString EquippedSpace)
{
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (!IsValid(ID)) return;
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (PCC == nullptr) return;
	if (PCC->RemoveEquippedItem(EquippedSpace, ID)) PCC->AddInventoryItem(ID);
	ReleasePutItem();
}

void UCInventoryItem::OnButtonClicked()
{
	FString ListViewName;
	if (GetOwningListView() == nullptr) return;
	GetOwningListView()->GetName(ListViewName);

	if (FPlatformTime::Seconds() - ClickedSec <= 0.35f)
	{
		//FString ListViewName;
		//GetOwningListView()->GetName(ListViewName);
		if (ListViewName == "ItemList") Equip();
		else UnEquip(ListViewName);

	}
	ClickedSec = FPlatformTime::Seconds();

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (ID == nullptr || UIController == nullptr) return;

	if (ListViewName != "ItemList" || ID->GetItemType() < 5) return;

	//SwitchbPicked();
	if (!bPicked)
	{
		if (GetOwningListView())
		{
			for (UUserWidget* UW : GetOwningListView()->GetDisplayedEntryWidgets())
			{
				UCInventoryItem* II = Cast<UCInventoryItem>(UW);
				if (II == nullptr || II == this) continue;
				II->ReleasePutItem();
			}
		}

		SetRenderOpacity(0.4f);
		bPicked = true;
		UE_LOG(LogTemp, Log, TEXT("bPicked True 134"));
		UIController->DragInItem(ID);
	}
	else
	{
		bPicked = false;
		SetRenderOpacity(1.f);
		UIController->DragOutItem();
	}
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
		PlayerState->SetHoverringUI(nullptr);
	}


	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	UIController->UnShowItemDetailUI();
}

void UCInventoryItem::OnButtonReleased()
{
}

void UCInventoryItem::OnButtonPressed()
{
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

void UCInventoryItem::ReleasePutItem()
{
	//UE_LOG(LogTemp, Log, TEXT("ReleasePutItem"));
	if (!bPicked) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	//SwitchbPicked(true, false);
	bPicked = false;
	SetRenderOpacity(1.f);
	UIController->DragOutItem();
}

void UCInventoryItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetOwningListView() != nullptr)
	{
		//FString ListViewName;
		//GetOwningListView()->GetName(ListViewName);
		UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
		//if (ListViewName == "ItemList" && ID != nullptr)
		if (ID != nullptr)
		{
			if (ID->GetItemType() >= 3)
			{
				ItemQuantity->SetText(FText::FromString(FString::FromInt(ID->GetItemCount())));
				ItemQuantity->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	if (bPicked == false) return;

	FVector2D MousePos;
	GetOwningPlayer()->GetMousePosition(MousePos.X, MousePos.Y);
	int32 X, Y;
	GetOwningPlayer()->GetViewportSize(X, Y);
	FVector2D ViewportSize = FVector2D(X / 2, Y / 2);
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UIController->DragItem(MousePos);
	//SetPositionInViewport(MousePos);
}

void UCInventoryItem::SwitchbPicked(bool bForce, bool e)
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if (ID == nullptr || UIController == nullptr) return;
	if (bForce ? e : !bPicked)
	{
		SetRenderOpacity(0.4f);
		if (GetOwningListView())
		{
			for (UUserWidget* UW : GetOwningListView()->GetDisplayedEntryWidgets())
			{
				UCInventoryItem* II = Cast<UCInventoryItem>(UW);
				if (II == nullptr || II == this) continue;
				II->ReleasePutItem();
			}
		}
		bPicked = true;
		UIController->DragInItem(ID);
	}
	if (bForce ? !e : bPicked)
	{
		bPicked = false;
		SetRenderOpacity(1.f);
		UIController->DragOutItem();
	}
}

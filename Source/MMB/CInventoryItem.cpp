// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventoryItem.h"
#include "CPlayerCharacter.h"
#include "CWeapon.h"
#include "IWeapon.h"
#include "IPlayerUIController.h"
#include "IPlayerState.h"
#include "GenericPlatform/GenericPlatformTime.h"

void UCInventoryItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = ListItemObject;
	//ItemName->SetText(FText::FromString(TEXT("ItemName")));

	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
		if (AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			UTexture2D* T = GM->IconGetter(ID->GetIconTexture());
			ItemImage->SetBrushFromTexture(T);
		}

		ItemName->SetText(FText::FromString(ID->GetstrName()));
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

	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ID->GetItemClass(), PC->GetActorLocation(), FRotator::ZeroRotator);
	IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor);
	if (isWeapon == nullptr) return;

	isWeapon->SetIsEquiped(true);
	isWeapon->SetWeaponName(FName(ID->GetstrName()));
	isWeapon->SetAttackDamage(ID->GetAttackDamage());

	PC->Equip(*spawnedActor);

	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(PC->GetController());

	if (PCC == nullptr) return;
	PCC->RemoveInventoryItem(ID);
}

void UCInventoryItem::OnButtonClicked()
{
	if (FPlatformTime::Seconds() - ClickedSec <= 0.35f)
	{
		Equip();
	}
	ClickedSec = FPlatformTime::Seconds();
}

void UCInventoryItem::OnHovered()
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	//PlayerState->SetState(PLAYER_INVENTORY_HOVERRING, true);
	if (PlayerState == nullptr) return;
	PlayerState->SetHoverringUI(this);
}

void UCInventoryItem::OnUnHovered()
{
	GetOwningPlayer()->GetWorld()->GetTimerManager().ClearTimer(UnHoverTimerHandler);
	GetOwningPlayer()->GetWorld()->GetTimerManager().SetTimer(UnHoverTimerHandler, FTimerDelegate::CreateLambda([&]() {
		IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
		//PlayerState->SetState(PLAYER_INVENTORY_HOVERRING, false);
		if (PlayerState == nullptr) return;
		PlayerState->SetHoverringUI(false);
		}), 0.5f, false
	);
}

void UCInventoryItem::OnRightClicked()
{
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	IIPlayerState* PC = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if ((PCC == nullptr || ID == nullptr) || !PCC->IsOnShop()) return;
	int ItemPrice = ID->GetPrice();
	PCC->RemoveInventoryItem(ID);
	PCC->ResumeShopInventoryItems();
	PC->GainPlayerGold(ItemPrice);

	//Equip();
}

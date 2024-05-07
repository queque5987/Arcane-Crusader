// Fill out your copyright notice in the Description page of Project Settings.


#include "CShopItem.h"

void UCShopItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
		ItemPrice->SetText(FText::FromString(FString::FromInt(ID->GetPrice())));
		ItemType->SetText(FText::FromString(ID->GetAttackType()));
		ItemATK->SetText(FText::FromString(FString::SanitizeFloat(ID->GetAttackDamage())));
		ItemName->SetText(FText::FromString(ID->GetstrName()));
	}
}

void UCShopItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton->OnClicked.RemoveDynamic(this, &UCInventoryItem::OnButtonClicked);
	ItemButton->OnClicked.AddDynamic(this, &UCShopItem::OnShopButtonClicked);
	ClickedSec = 0.f;
}

void UCShopItem::OnShopButtonClicked()
{
	if (FPlatformTime::Seconds() - ClickedSec <= 0.35f)
	{
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(this->GetOwningPlayer()->GetCharacter());
		UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
		ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());

		int32 PlayerGold = PC->GetPlayerGold();
		int32 Price = ID->GetPrice();
		if (Price > PlayerGold)
		{
			if (IsValid(PCC))
			{
				PCC->AddAlert(FText::FromString(TEXT("Not Enough Gold")));
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("TODO // U Cant Buy It Alert"));
			}
			return;
		}
		if (IsValid(ID) && IsValid(PCC))
		{
			PC->SetPlayerGold(PlayerGold - Price);
			//PCC->AddInventoryItem(ID->GetItemClass());
			PCC->AddInventoryItem(ID);
		}
	}
	ClickedSec = FPlatformTime::Seconds();
}

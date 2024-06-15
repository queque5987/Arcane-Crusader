// Fill out your copyright notice in the Description page of Project Settings.


#include "CShopItem.h"
#include "Styling/SlateWidgetStyleAsset.h"
#include "IItemManager.h"

void UCShopItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
		ItemPrice->SetText(FText::FromString(FString::FromInt(ID->GetPrice())));
		//ItemType->SetText(FText::FromString(ID->GetAttackType()));
		//ItemATK->SetText(FText::FromString(FString::SanitizeFloat(ID->GetAttackDamage())));
		ItemName->SetText(FText::FromString(ID->GetstrName()));
		IsShopItem = ID->GetIsShopItem();
	}

	USlateWidgetStyleAsset* Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ShopItem.SlateStyle_ShopItem"));
	const FButtonStyle* btnStyle = Style->GetStyle<FButtonStyle>();
	if (USlateWidgetStyleAsset* ST = Cast<USlateWidgetStyleAsset>(Style))
	{
		ItemButton->WidgetStyle = *btnStyle;
		SB_Normal = &btnStyle->Normal;
		SB_Pressed = &btnStyle->Pressed;
	}
	bPressed = false;
}

void UCShopItem::OnRightClicked()
{
	if (!IsShopItem)
	{
		SellItem();
	}
	else
	{
		BuyItem();
	}
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
		ItemButton->WidgetStyle.SetNormal(*SB_Pressed);
		UIController->SetPressedButton(this);
	}
	else
	{
		bPressed = false;
		ItemButton->WidgetStyle.SetNormal(*SB_Normal);
	}
}

void UCShopItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton->OnClicked.RemoveDynamic(this, &UCInventoryItem::OnButtonClicked);
	ItemButton->OnClicked.AddDynamic(this, &UCShopItem::OnShopButtonClicked);
	ClickedSec = 0.f;
}

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
	//PCC->AddInventoryItem(ID);
	PCC->AddInventoryItem(NewID);
	PCC->ResumeShopInventoryItems();
}

void UCShopItem::SellItem()
{
	IIPlayerUIController* PCC = Cast<IIPlayerUIController>(GetOwningPlayer());
	IIPlayerState* PC = Cast<IIPlayerState>(GetOwningPlayer()->GetCharacter());
	UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
	if ((PCC == nullptr || ID == nullptr) || !PCC->IsOnShop()) return;
	int iItemPrice = ID->GetPrice();
	PCC->RemoveInventoryItem(ID);
	PCC->ResumeShopInventoryItems();
	PC->GainPlayerGold(iItemPrice);
	Destruct();
}

void UCShopItem::OnShopButtonClicked()
{
	if (FPlatformTime::Seconds() - ClickedSec <= 0.35f)
	{
		//UWidget* RootWidget = GetRootWidget();

		//BuyItem();
		//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(this->GetOwningPlayer()->GetCharacter());
		//UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);
		//ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());

		//int32 PlayerGold = PC->GetPlayerGold();
		//int32 Price = ID->GetPrice();
		//if (Price > PlayerGold)
		//{
		//	if (IsValid(PCC))
		//	{
		//		PCC->AddAlert(FText::FromString(TEXT("Not Enough Gold")));
		//	}
		//	else
		//	{
		//		UE_LOG(LogTemp, Log, TEXT("TODO // U Cant Buy It Alert"));
		//	}
		//	return;
		//}
		//if (IsValid(ID) && IsValid(PCC))
		//{
		//	PC->SetPlayerGold(PlayerGold - Price);
		//	//PCC->AddInventoryItem(ID->GetItemClass());
		//	PCC->AddInventoryItem(ID);
		//	PCC->ResumeShopInventoryItems();
		//}
	}
	ClickedSec = FPlatformTime::Seconds();


	SwitchPressed(!bPressed);
}

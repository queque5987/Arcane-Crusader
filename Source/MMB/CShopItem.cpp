// Fill out your copyright notice in the Description page of Project Settings.


#include "CShopItem.h"
#include "Styling/SlateWidgetStyleAsset.h"
#include "IItemManager.h"
#include "Materials/MaterialInstanceDynamic.h"

void UCShopItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
		ItemPrice->SetText(FText::FromString(FString::FromInt(ID->GetPrice())));
		ItemName->SetText(FText::FromString(ID->GetstrName()));
		IsShopItem = ID->GetIsShopItem();
	}

	bPressed = false;
	CurrentTextureIndex = 0.f;

	if (ItemSelectSpriteMaterial != nullptr)
	{
		FVector RarityColor;
		switch (Rarity)
		{
		case(ITEM_RARE):
			RarityColor = FVector(0.176293f, 0.559561f, 1.f);
			break;

		case(ITEM_EPIC):
			RarityColor = FVector(0.47264f, 0.f, 0.734375f);
			break;

		case(ITEM_LEGENDARY):
			RarityColor = FVector(1.f, 0.610103f, 0.268382f);
			break;

		case(ITEM_NORMAL):
		default:
			RarityColor = FVector(1.f, 0.962442f, 0.99769f);
			break;
		}
		ItemSelectSpriteMaterial->SetVectorParameterValue("TextureColorOverride", RarityColor);
		UE_LOG(LogTemp, Log, TEXT("TextureColorOverride %s Set %s"), *ItemName->GetText().ToString(), *RarityColor.ToString());
	}
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
		//ItemButton->WidgetStyle.SetNormal(*SB_Pressed);
		UIController->SetPressedButton(this);
	}
	else
	{
		bPressed = false;
		CurrentTextureIndex = 0.f;
		//ItemButton->WidgetStyle.SetNormal(*SB_Normal);
	}
}

void UCShopItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton->OnClicked.RemoveDynamic(this, &UCInventoryItem::OnButtonClicked);
	ItemButton->OnClicked.AddDynamic(this, &UCShopItem::OnShopButtonClicked);
	ClickedSec = 0.f;

	if (ItemSelectSprite != nullptr) ItemSelectSpriteMaterial = ItemSelectSprite->GetDynamicMaterial();
	if (ItemSelectSpriteMaterial == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemSelectSpriteMaterial Not Found"));
	}
}

void UCShopItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (ItemSelectSpriteMaterial != nullptr)
	{
		ItemSelectSpriteMaterial->SetScalarParameterValue("TextureIndex", CurrentTextureIndex);
		
		//UE_LOG(LogTemp, Log, TEXT("Set TextureIndex To %f"), CurrentTextureIndex);
	}

	if (bPressed)
	{
		CurrentTextureIndex += InDeltaTime * 10.f;
		//UE_LOG(LogTemp, Log, TEXT("Should GIF Be Working"));
	}
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
	
	if (ID->GetItemCount() > 1)
	{
		ID->SetItemCount(ID->GetItemCount() - 1);
	}
	else
	{
		PCC->RemoveInventoryItem(ID);
		PCC->ResumeShopInventoryItems();
	}

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

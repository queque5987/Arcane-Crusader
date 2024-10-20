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
			RarityColor = RGB_RARE;
			break;
		case(ITEM_EPIC):
			RarityColor = RGB_EPIC;
			break;
		case(ITEM_LEGENDARY):
			RarityColor = RGB_LEGENDARY;
			break;
		case(ITEM_NORMAL):
		default:
			RarityColor = RGB_NORMAL;
			break;
		}
		ItemSelectSpriteMaterial->SetVectorParameterValue("TextureColorOverride", RarityColor);
		UE_LOG(LogTemp, Log, TEXT("TextureColorOverride %s Set %s"), *ItemName->GetText().ToString(), *RarityColor.ToString());
	}

	ItemImageSize = 100.f;
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
	ItemButton->OnHovered.AddDynamic(this, &UCShopItem::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UCShopItem::OnUnHovered);

	ClickedSec = 0.f;
	bHovered = false;

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
	//if (bPressed || bHovered)
	//{
	//	CurrentTextureIndex += InDeltaTime * 10.f;
	//	//UE_LOG(LogTemp, Log, TEXT("Should GIF Be Working"));
	//}
}

void UCShopItem::OnHovered()
{
	Super::OnHovered();

	bHovered = true;
}

void UCShopItem::OnUnHovered()
{
	Super::OnUnHovered();

	bHovered = false;
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

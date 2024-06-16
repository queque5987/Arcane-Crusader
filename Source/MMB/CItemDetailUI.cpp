// Fill out your copyright notice in the Description page of Project Settings.


#include "CItemDetailUI.h"
#include "CInventoryItemData.h"
#include "IItemManager.h"
#include "PCH.h"
#include "MMBGameModeBase.h"

UCItemDetailUI::UCItemDetailUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultPos = GetRenderTransform().Translation;
}

void UCItemDetailUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D MousePos;
	GetOwningPlayer()->GetMousePosition(MousePos.X, MousePos.Y);

	int Vx, Vy;
	FVector2D DS = MainPannel->GetDesiredSize();
	GetOwningPlayer()->GetViewportSize(Vx, Vy);
	if (Vx - MousePos.X <= DS.X) MousePos.X -= DS.X - (Vx - MousePos.X);
	//if (Vy - MousePos.Y <= DS.Y) MousePos.Y -= DS.Y - (Vy - MousePos.Y);

	SetPositionInViewport(MousePos);
}

void UCItemDetailUI::SetDetail(UCInventoryItemData* ItemData)
{
	if (IIItemManager* GM = Cast<IIItemManager>(GetWorld()->GetAuthGameMode()))
	{
		UTexture2D* T = GM->IconGetter(ItemData->GetIconTexture());
		ItemImage->SetBrushFromTexture(T);
	}

	ItemName->SetText(FText::FromString(ItemData->GetstrName()));
	ItemPrice->SetText(FText::FromString(FString::FromInt(ItemData->GetPrice())));
	ItemDetail->SetText(ItemData->GetItemDetail());

	//ItemStat Stats;
	//ItemData->GetItemStats(Stats);
	ItemStat* Stats = ItemData->GetItemStats();
	FString tempStat;
	FString tempStatDesc;
	bool EnterFlag = false;
	if (Stats->_AttackDamage != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("공격력");
		if (Stats->_AttackDamage > 0) tempStatDesc += "+ ";
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_AttackDamage);
		EnterFlag = true;
	}
	if (Stats->_Defence != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("방어력");
		tempStatDesc += "+ ";
		//tempStatDesc += FString::SanitizeFloat(Stats->_Defence);
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_Defence);
		EnterFlag = true;
	}
	if (Stats->_AttackSpeed != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("공격속도");
		if (Stats->_AttackSpeed > 0) tempStatDesc += "+ ";
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_AttackSpeed * 100.f);
		//tempStatDesc += FString::SanitizeFloat(Stats->_AttackSpeed * 100.f);
		tempStatDesc += "%";
		EnterFlag = true;
	}

	//Potion
	if (ItemData->GetItemType() == 5 && Stats->_HealPoint != 0.f)
	{
		if (EnterFlag)
		{
			tempStat += "\n";
			tempStatDesc += "\n";
		}
		tempStat += TEXT("체력 회복");
		if (Stats->_HealPoint > 0) tempStatDesc += "+ ";
		else tempStatDesc += "- ";
		tempStatDesc += FString::Printf(TEXT("%.0f"), Stats->_HealPoint);
		EnterFlag = true;
	}

	ItemStatText->SetText(FText::FromString(tempStat));
	ItemStatDescText->SetText(FText::FromString(tempStatDesc));

	//switch (ItemData->GetItemType())
	//{
	//case(ITEM_TYPE_WEAPON):
	//	ItemATK->SetText(FText::FromString(FString::SanitizeFloat(ItemData->GetAttackDamage())));
	//	WeaponPannel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//	break;
	//default:
	//	WeaponPannel->SetVisibility(ESlateVisibility::Hidden);
	//	break;
	//}
}

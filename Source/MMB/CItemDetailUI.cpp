// Fill out your copyright notice in the Description page of Project Settings.


#include "CItemDetailUI.h"
#include "CInventoryItemData.h"
#include "IItemManager.h"
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
	ItemATK->SetText(FText::FromString(FString::SanitizeFloat(ItemData->GetAttackDamage())));
}

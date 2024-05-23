// Fill out your copyright notice in the Description page of Project Settings.


#include "CWidgetDroppedItem.h"

void UCWidgetDroppedItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (UCInventoryItemData* D = Cast<UCInventoryItemData>(ListItemObject))
	{
		ItemName->SetText(FText::FromString(D->GetstrName()));
		if (AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			UTexture2D* T = GM->IconGetter(D->GetIconTexture());
			//UTexture2D* T = GM->GetPreLoadedTexture(D->GetIconTexture());
			ItemImage->SetBrushFromTexture(T);
		}
	}	
}
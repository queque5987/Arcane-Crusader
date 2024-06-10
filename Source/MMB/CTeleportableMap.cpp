// Fill out your copyright notice in the Description page of Project Settings.


#include "CTeleportableMap.h"
#include "IPlayerUIController.h"
#include "GameFramework/Character.h"
#include "Styling/SlateWidgetStyleAsset.h"

void UCTeleportableMap::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	MapData = Cast<UCTeleportableMapData>(ListItemObject);
	if (MapData != nullptr) MapName->SetText(FText::FromName(MapData->GetDestLevelName()));

	//UObject* Style = StaticLoadObject(USlateWidgetStyleAsset::StaticClass(), nullptr, *MapData->GetPreviewSlateBrush());
	//UObject* L = StaticLoadObject(USlateBrushAsset::StaticClass(), nullptr, *MapData->GetPreviewSlateBrush());
	USlateWidgetStyleAsset* Style = LoadObject<USlateWidgetStyleAsset>(nullptr, *MapData->GetPreviewSlateBrush());
	if (Style != nullptr)
	{
		const FButtonStyle* btnStyle = Style->GetStyle<FButtonStyle>();
		if (USlateWidgetStyleAsset* ST = Cast<USlateWidgetStyleAsset>(Style))
		{
			//ST->GetStyle()
			BtnMapPreview->WidgetStyle = *btnStyle;
			//BtnMapPreview->WidgetStyle.SetNormal(SB->Brush);
			//BtnMapPreview->WidgetStyle.SetHovered(SB->Brush);
			//BtnMapPreview->WidgetStyle.SetPressed(SB->Brush);
			//SB_Normal = btnStyle->Normal;
			SB_Normal = BtnMapPreview->WidgetStyle.Normal;
			SB_Pressed = BtnMapPreview->WidgetStyle.Pressed;
			//SB_Pressed = btnStyle->Pressed;
		}
	}
	bPressed = false;
}

void UCTeleportableMap::NativeOnInitialized()
{
	BtnMapPreview->OnClicked.AddDynamic(this, &UCTeleportableMap::OnButtonClicked);
}

void UCTeleportableMap::OnButtonClicked()
{
	if (MapData == nullptr) return;

	IIPlayerUIController* IAC = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (IAC == nullptr) return;
	if (!bPressed)
	{
		bPressed = true;
		IAC->SetSelectedPortal(MapData->GetArrIndex());

		//const FSlateBrush tempNormalBrush = BtnMapPreview->WidgetStyle.Normal;
		//const FSlateBrush tempPressedBrush = BtnMapPreview->WidgetStyle.Pressed;
		//BtnMapPreview->WidgetStyle.SetNormal(tempPressedBrush);
		//BtnMapPreview->WidgetStyle.SetPressed(tempNormalBrush);

		BtnMapPreview->WidgetStyle.SetNormal(SB_Pressed);
	}
	else
	{
		bPressed = false;
		IAC->SetSelectedPortal(-1);

		//const FSlateBrush tempNormalBrush = BtnMapPreview->WidgetStyle.Normal;
		//const FSlateBrush tempPressedBrush = BtnMapPreview->WidgetStyle.Pressed;
		//BtnMapPreview->WidgetStyle.SetNormal(tempPressedBrush);
		//BtnMapPreview->WidgetStyle.SetPressed(tempNormalBrush);
		BtnMapPreview->WidgetStyle.SetNormal(SB_Normal);
	}
}

void UCTeleportableMap::SwitchPressed(bool Pressed)
{
	if (MapData == nullptr) return;

	if (Pressed)
	{
		IIPlayerUIController* IAC = Cast<IIPlayerUIController>(GetOwningPlayer());
		if (IAC == nullptr) return;

		bPressed = true;
		IAC->SetSelectedPortal(MapData->GetArrIndex());

		//const FSlateBrush tempNormalBrush = BtnMapPreview->WidgetStyle.Normal;
		//const FSlateBrush tempPressedBrush = BtnMapPreview->WidgetStyle.Pressed;
		//BtnMapPreview->WidgetStyle.SetNormal(tempPressedBrush);
		//BtnMapPreview->WidgetStyle.SetPressed(tempNormalBrush);
		BtnMapPreview->WidgetStyle.SetNormal(SB_Pressed);
	}
	else
	{
		IIPlayerUIController* IAC = Cast<IIPlayerUIController>(GetOwningPlayer());
		if (IAC == nullptr) return;
		bPressed = false;
		//IAC->SetSelectedPortal(-1);

		//const FSlateBrush tempNormalBrush = BtnMapPreview->WidgetStyle.Normal;
		//const FSlateBrush tempPressedBrush = BtnMapPreview->WidgetStyle.Pressed;
		//BtnMapPreview->WidgetStyle.SetNormal(tempPressedBrush);
		//BtnMapPreview->WidgetStyle.SetPressed(tempNormalBrush);
		BtnMapPreview->WidgetStyle.SetNormal(SB_Normal);
	}
}

bool UCTeleportableMap::GetbPressed()
{
	return bPressed;
}

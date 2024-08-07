// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidgetPlayerHUD.h"
#include "IPlayerUIController.h"
#include "CInventoryItemData.h"
#include "CUserWidget_CircularProgressBar.h"

UCUserWidgetPlayerHUD::UCUserWidgetPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InitializeUI();
}

void UCUserWidgetPlayerHUD::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (InVisibility == ESlateVisibility::Visible) InitializeUI();
}

void UCUserWidgetPlayerHUD::InitializeUI()
{
	bContinueRevive = false;

	if (DieUI == nullptr) return;
	DieUI->SetVisibility(ESlateVisibility::Hidden);

	FLinearColor Color = FLinearColor(1.f, 0.f, 0.f, 0.1f);
	DieBG->SetColorAndOpacity(Color);
	//DieBG->GetColorAndOpacity().A = 0.1f;

	//DieText->GetFont().LetterSpacing = 0.f;
	FSlateFontInfo Font = DieText->GetFont();
	Font.LetterSpacing = 0.f;
	DieText->SetFont(Font);

	DieSubText->SetVisibility(ESlateVisibility::Hidden);
	DieSubText->SetRenderOpacity(0.0f);

	QuickSlot_1->OnPressed.AddDynamic(this, &UCUserWidgetPlayerHUD::OnClickQuickSlot1);
	QuickSlot_2->OnPressed.AddDynamic(this, &UCUserWidgetPlayerHUD::OnClickQuickSlot2);
	QuickSlot_3->OnPressed.AddDynamic(this, &UCUserWidgetPlayerHUD::OnClickQuickSlot3);
}

void UCUserWidgetPlayerHUD::ShowDieUI(bool b)
{
	DieUI->SetVisibility(b ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (!b) InitializeUI();
}

void UCUserWidgetPlayerHUD::Tick_DieUIAnim(float DeltaTime)
{
	if (DieBG->GetColorAndOpacity().A <= 0.3f)
	{
		FLinearColor Color = DieBG->GetColorAndOpacity();
		Color.A += 0.05 * DeltaTime;
		DieBG->SetColorAndOpacity(Color);
	}
	if (DieText->GetFont().LetterSpacing <= 1200.f)
	{
		FSlateFontInfo Font = DieText->GetFont();
		Font.LetterSpacing += 300.f * DeltaTime;
		DieText->SetFont(Font);
	}
	if (DieText->GetFont().LetterSpacing > 1000.f)
	{
		if (DieSubText->GetVisibility() == ESlateVisibility::Hidden) DieSubText->SetVisibility(ESlateVisibility::Visible);
		float DieSubTextOpacity = DieSubText->GetRenderOpacity();
		if (DieSubTextOpacity >= 1.f) return;
		if (!bContinueRevive && DieSubTextOpacity >= 0.6f) bContinueRevive = true;
		DieSubText->SetRenderOpacity(DieSubTextOpacity += 0.35f * DeltaTime);
	}
}

void UCUserWidgetPlayerHUD::OnClickQuickSlot1()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot1Item = UIController->GetQuickSlot();
	
	QuickSlot_1_Tile->ClearListItems();
	if (QuickSlot1Item != nullptr) QuickSlot_1_Tile->AddItem(QuickSlot1Item);
}

void UCUserWidgetPlayerHUD::OnClickQuickSlot2()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot2Item = UIController->GetQuickSlot();
	
	QuickSlot_2_Tile->ClearListItems();
	if (QuickSlot2Item != nullptr) QuickSlot_2_Tile->AddItem(QuickSlot2Item);
}

void UCUserWidgetPlayerHUD::OnClickQuickSlot3()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot3Item = UIController->GetQuickSlot();
	
	QuickSlot_3_Tile->ClearListItems();
	if (QuickSlot3Item != nullptr) QuickSlot_3_Tile->AddItem(QuickSlot3Item);
}

FString UCUserWidgetPlayerHUD::GetItemDataOnQuickSlot(int32 QuickSlotNum)
{
	//IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	//if (UIController == nullptr) return "";

	UCInventoryItemData* tempID = nullptr;
	switch (QuickSlotNum)
	{
	case(1):
		tempID = Cast<UCInventoryItemData>(QuickSlot_1_Tile->GetItemAt(0));
		break;
	case(2):
		tempID = Cast<UCInventoryItemData>(QuickSlot_2_Tile->GetItemAt(0));
		break;
	case(3):
		tempID = Cast<UCInventoryItemData>(QuickSlot_3_Tile->GetItemAt(0));
		break;
	default:
		break;
	}
	if (tempID == nullptr) return "";
	return tempID->GetstrName();
}

void UCUserWidgetPlayerHUD::SetAimVisibility(bool e)
{
	AimSpot->SetVisibility(e ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void UCUserWidgetPlayerHUD::SetQuickSlot1(UCInventoryItemData* QuickItem)
{
	QuickSlot_1_Tile->ClearListItems();
	QuickSlot_1_Tile->AddItem(QuickItem);
}

void UCUserWidgetPlayerHUD::SetQuickSlot2(UCInventoryItemData* QuickItem)
{
	QuickSlot_2_Tile->ClearListItems();
	QuickSlot_2_Tile->AddItem(QuickItem);
}

void UCUserWidgetPlayerHUD::SetQuickSlot3(UCInventoryItemData* QuickItem)
{
	QuickSlot_3_Tile->ClearListItems();
	QuickSlot_3_Tile->AddItem(QuickItem);
}

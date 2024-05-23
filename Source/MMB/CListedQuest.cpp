// Fill out your copyright notice in the Description page of Project Settings.


#include "CListedQuest.h"
#include "IPlayerUIController.h"

void UCListedQuest::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	QuestData = ListItemObject;

	UCQuestData* QD = Cast<UCQuestData>(QuestData);
	if (QD == nullptr) return;

	FString Qname = QD->GetQuestName();
	QuestName->SetText(FText::FromString(Qname));


	USlateWidgetStyleAsset* Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ShopItem.SlateStyle_ShopItem"));
	const FButtonStyle* btnStyle = Style->GetStyle<FButtonStyle>();
	if (USlateWidgetStyleAsset* ST = Cast<USlateWidgetStyleAsset>(Style))
	{
		BtnQuest->WidgetStyle = *btnStyle;
		SB_Normal = &btnStyle->Normal;
		SB_Pressed = &btnStyle->Pressed;
	}
	bPressed = false;
}

void UCListedQuest::SwitchPressed(bool Pressed)
{
	if (Pressed == bPressed) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	if (Pressed)
	{
		bPressed = true;
		BtnQuest->WidgetStyle.SetNormal(*SB_Pressed);
		UIController->SetPressedButton(this);
	}
	else
	{
		bPressed = false;
		BtnQuest->WidgetStyle.SetNormal(*SB_Normal);
	}
}

void UCListedQuest::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnQuest->OnClicked.AddDynamic(this, &UCListedQuest::OnButtonClicked);
}

void UCListedQuest::OnButtonClicked()
{
	SwitchPressed(!bPressed);
}

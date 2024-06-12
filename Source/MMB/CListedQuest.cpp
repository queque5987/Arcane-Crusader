// Fill out your copyright notice in the Description page of Project Settings.


#include "CListedQuest.h"
#include "IPlayerUIController.h"

UCListedQuest::UCListedQuest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FSlateColor Quest_No_Match			 = FSlateColor(FColor(1.f, 1.f, 1.f, 1.f));
	FSlateColor Quest_Aleary_Have		 = FSlateColor(FColor(1.f, 0.798223f, 0.108477f, 1.f));
	FSlateColor Quest_Cleared			 = FSlateColor(FColor(0.267188f, 1.f, 0.123389f, 1.f));
	FSlateColor Quest_Aleardy_Cleared	 = FSlateColor(FColor(0.2f, 0.2f, 0.2f, 1.f));

	QuestState_BackGroundColorArr.Add(&Quest_No_Match);
	QuestState_BackGroundColorArr.Add(&Quest_Aleary_Have);
	QuestState_BackGroundColorArr.Add(&Quest_Cleared);
	QuestState_BackGroundColorArr.Add(&Quest_Aleardy_Cleared);
}

void UCListedQuest::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	QuestData = ListItemObject;

	UCQuestData* QD = Cast<UCQuestData>(QuestData);
	if (QD == nullptr) return;

	FString Qname = QD->GetQuestName();
	QuestName->SetText(FText::FromString(Qname));
	QuestState = QD->GetQuestState();

	USlateWidgetStyleAsset* Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_Normal.SlateStyle_ListedQuest_Normal"));

	const FButtonStyle* btnStyle = Style->GetStyle<FButtonStyle>();
	
	if (USlateWidgetStyleAsset* ST = Cast<USlateWidgetStyleAsset>(Style))
	{
		BtnQuest->WidgetStyle = *btnStyle;
		//SB_Normal = &btnStyle->Normal;
		//SB_Pressed = &btnStyle->Pressed;
		SB_Normal = BtnQuest->WidgetStyle.Normal;
		SB_Pressed = BtnQuest->WidgetStyle.Pressed;
	}

	bPressed = false;

	ResumeButtonStyle();
}

void UCListedQuest::SwitchPressed(bool Pressed)
{
	if (Pressed == bPressed) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;
	if (Pressed)
	{
		bPressed = true;
		//BtnQuest->WidgetStyle.SetNormal(*SB_Pressed);
		BtnQuest->WidgetStyle.SetNormal(SB_Pressed);
		UIController->SetPressedButton(this);
	}
	else
	{
		bPressed = false;
		//BtnQuest->WidgetStyle.SetNormal(*SB_Normal);
		BtnQuest->WidgetStyle.SetNormal(SB_Normal);
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

void UCListedQuest::ResumeButtonStyle()
{
	UCQuestData* QD = Cast<UCQuestData>(QuestData);
	if (QD == nullptr) return;

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	QuestState = UIController->IsPossesQuestCleared(QD->GetQuestName());
	if (!UIController->IsQualifiedQuest(QD->GetRequiredQuest()))
	{
		QuestState = 4;
	}
	//if (QuestState == 0 && !UIController->IsQualifiedQuest(QD->GetRequiredQuest()))
	//{
	//	QuestState = 4;
	//}

	USlateWidgetStyleAsset* Style;
	switch (QuestState)
	{
	case(1):
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_AlreadyHave.SlateStyle_ListedQuest_AlreadyHave"));
		break;
	case(2):
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_Cleared.SlateStyle_ListedQuest_Cleared"));
		break;
	case(3):
	case(4):
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_AlreadyCleared.SlateStyle_ListedQuest_AlreadyCleared"));
		break;
	default:
		Style = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/Resources/Image/SlateStyle/SlateStyle_ListedQuest_Normal.SlateStyle_ListedQuest_Normal"));
	}

	const FButtonStyle* btnStyle = Style->GetStyle<FButtonStyle>();

	if (USlateWidgetStyleAsset* ST = Cast<USlateWidgetStyleAsset>(Style))
	{
		BtnQuest->WidgetStyle = *btnStyle;
		//SB_Normal = &btnStyle->Normal;
		//SB_Pressed = &btnStyle->Pressed;
		SB_Normal = BtnQuest->WidgetStyle.Normal;
		SB_Pressed = BtnQuest->WidgetStyle.Pressed;
	}
}

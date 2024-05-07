// Fill out your copyright notice in the Description page of Project Settings.


#include "CNPCConversationButton.h"
#include "CNPCConversationButtonData.h"

void UCNPCConversationButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ButtonData = ListItemObject;
	
	UCNPCConversationButtonData* D = Cast<UCNPCConversationButtonData>(ButtonData);
	if (D != nullptr)
	{
		BtnText->SetText(FText::FromName(D->GetBtnName()));
		//Clickevent = D->GetClickEvent();
		Btn->OnClicked.AddDynamic(this, &UCNPCConversationButton::OnClicked);
		ClickDele = D->GetClickDele();
	}
}

void UCNPCConversationButton::OnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Btn %s Clicked"), *BtnText->GetText().ToString());
	if (ClickDele->ExecuteIfBound())
	{
		UE_LOG(LogTemp, Log, TEXT("**Btn %s Delegate Sent"), *BtnText->GetText().ToString());
	}
}

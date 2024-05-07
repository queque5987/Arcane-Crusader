// Fill out your copyright notice in the Description page of Project Settings.


#include "CButtonAction.h"

void UCButtonAction::NativeOnInitialized()
{
	Button->OnClicked.AddDynamic(this, &UCButtonAction::OnButtonTriggered);
}

void UCButtonAction::SetNPC(ACStaticNPC* e)
{
	NPC = e;
	NPCName->SetText(FText::FromString(e->GetName()));
}

void UCButtonAction::OnButtonTriggered()
{
}

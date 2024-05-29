// Fill out your copyright notice in the Description page of Project Settings.


#include "CButtonAction.h"

void UCButtonAction::NativeOnInitialized()
{
	Button->OnClicked.AddDynamic(this, &UCButtonAction::OnButtonTriggered);
}

void UCButtonAction::SetNPC(ACStaticNPC* e)
{
	NPC = e;
	//NPCName->SetText(FText::FromString(e->GetName()));
}

void UCButtonAction::SetRope(ACClimbableRope* e)
{
	Rope = e;
	NPCName->SetText(FText::FromString(TEXT("매달리기")));
}

void UCButtonAction::SetJumpPoints(ACJumpPoints* e)
{
	JumpPoints = e;
	NPCName->SetText(FText::FromString(TEXT("점프")));
}

void UCButtonAction::SetButtonMode(int e)
{
	ButtonMode = e;

	switch (e)
	{
	case(INTERACT_BUTTON_MODE_NPCDIALOGUE):
		NPCName->SetText(FText::FromString(TEXT("대화하기")));
		return;
	case(INTERACT_BUTTON_MODE_CLIMBROPE):
		NPCName->SetText(FText::FromString(TEXT("매달리기")));
		return;
	case(INTERACT_BUTTON_MODE_JUMPPOINTS):
		NPCName->SetText(FText::FromString(TEXT("뛰기")));
		return;
	case(INTERACT_BUTTON_MODE_PICKUPITEM):
		NPCName->SetText(FText::FromString(TEXT("줍기")));
		return;
	}
}

void UCButtonAction::OnButtonTriggered()
{
}

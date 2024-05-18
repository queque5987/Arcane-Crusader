// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidgetPlayerHUD.h"

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

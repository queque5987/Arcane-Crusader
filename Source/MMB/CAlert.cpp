// Fill out your copyright notice in the Description page of Project Settings.


#include "CAlert.h"

void UCAlert::NativeOnInitialized()
{
	AlertWindowBtn->OnClicked.AddDynamic(this, &UCAlert::OnClickedEvent);
	UpdateCanTick();
}

void UCAlert::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (DestructCount >= 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("Time Left %f"), DestructCount);
		DestructCount -= InDeltaTime;
		SetRenderOpacity(GetRenderOpacity()-InDeltaTime/0.8);
	}
	else if (DestructCount < 0.f)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCAlert::SetWindowLocation(FVector2D e)
{
	const FWidgetTransform CurrentTransform = AlertWindow->GetRenderTransform();
	AlertWindow->SetRenderTransform(FWidgetTransform(e, CurrentTransform.Scale, CurrentTransform.Shear, CurrentTransform.Angle));
	
}

void UCAlert::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (InVisibility == ESlateVisibility::Visible)
	{
		SetRenderOpacity(1.f);
		DestructCount = 0.8f;
	}
}

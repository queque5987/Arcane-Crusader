// Fill out your copyright notice in the Description page of Project Settings.


#include "CDamageUI.h"

void UCDamageUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (GetRenderOpacity() <= 0.f) Destruct();
	SetRenderOpacity(GetRenderOpacity() - InDeltaTime);
	FWidgetTransform T = GetRenderTransform();
	FVector2D newLocation = T.Translation + FVector2D(0.f, InDeltaTime*20);
	T.Translation = newLocation;
	SetRenderTransform(T);
}

void UCDamageUI::SetDamage(float e)
{
	if (e < 10.f)
	{
		float tempE = FMath::RoundToFloat(e * 10.f) / 10.f;
		if (FMath::Frac(tempE) > 0.f)
		{
			Damage->SetText(FText::FromString(FString::SanitizeFloat(tempE)));
			return;
		}
	}
	Damage->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(e))));
}

void UCDamageUI::SetDamageColor(FColor C)
{
	Damage->SetColorAndOpacity(FSlateColor(C));
}

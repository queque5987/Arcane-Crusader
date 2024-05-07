// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "PCH.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_InputDisabled.generated.h"

UCLASS()
class MMB_API UCUserWidget_InputDisabled : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	bool AllowInput = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CDamageUI.generated.h"

UCLASS()
class MMB_API UCDamageUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Damage;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void SetDamage(float e);
	void SetDamageColor(FColor C);
};

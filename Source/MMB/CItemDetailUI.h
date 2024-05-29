// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "CItemDetailUI.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCItemDetailUI : public UUserWidget
{
	GENERATED_BODY()

	UCItemDetailUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> MainPannel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPrice;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDetail;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> WeaponPannel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemATK;
protected:
	FVector2D DefaultPos;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void SetDetail(class UCInventoryItemData* ItemData);
};

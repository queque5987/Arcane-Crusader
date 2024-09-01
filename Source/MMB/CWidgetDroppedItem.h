// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CInventoryItemData.h"
#include "MMBGameModeBase.h"
#include "CWidgetDroppedItem.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCWidgetDroppedItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemGlowingSprite;

protected:

	int32 Rarity;

	class UMaterialInstanceDynamic* ItemGlowingSpriteMaterial;
	float CurrentTextureIndex;

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};

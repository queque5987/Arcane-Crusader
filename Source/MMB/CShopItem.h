// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CInventoryItem.h"
#include "PCH.h"
#include "CShopItem.generated.h"

UCLASS()
class MMB_API UCShopItem : public UCInventoryItem
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UImage> ItemImage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPrice;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemType;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemATK;
	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UTextBlock> ItemName;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION(BlueprintCallable)
	void OnShopButtonClicked();

};

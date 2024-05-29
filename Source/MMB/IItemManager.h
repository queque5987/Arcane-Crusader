// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IItemManager.generated.h"

UINTERFACE(MinimalAPI)
class UIItemManager : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIItemManager
{
	GENERATED_BODY()

public:
	virtual UTexture2D* IconGetter(FString IconAssetName) { return nullptr; };

	virtual class UCInventoryItemData* GetItem(FName ItemRowName, int Count = 1) { return nullptr; }
};

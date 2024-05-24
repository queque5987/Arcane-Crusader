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

	virtual class UCInventoryItemData* GetItem(FName ItemRowName) { return nullptr; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CustomDataTables.h"
#include "IPortalNPC.generated.h"

UINTERFACE(MinimalAPI)
class UIPortalNPC : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIPortalNPC
{
	GENERATED_BODY()

public:
	virtual void GetTeleportableMaps(TArray<struct FTeleportableMapTableRow*>& Arr) {}
	
};

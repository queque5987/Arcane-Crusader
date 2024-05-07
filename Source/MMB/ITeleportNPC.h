// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CustomDataTables.h"
#include "ITeleportNPC.generated.h"

UINTERFACE(MinimalAPI)
class UITeleportNPC : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IITeleportNPC
{
	GENERATED_BODY()

public:
	virtual TArray<struct FTeleportableMapTableRow*> GetLoadedMap() { return TArray<struct FTeleportableMapTableRow*>(); }
};

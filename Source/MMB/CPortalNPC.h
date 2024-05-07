// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CStaticNPC.h"
#include "CustomDataTables.h"
#include "IPortalNPC.h"
#include "CPortalNPC.generated.h"

UCLASS()
class MMB_API ACPortalNPC : public ACStaticNPC, public IIPortalNPC
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UDataTable* MapTable;
	UPROPERTY(EditAnywhere)
	TArray<FText> ReachableMaps;

public:
	virtual void GetTeleportableMaps(TArray<struct FTeleportableMapTableRow*>& Arr) override;

};

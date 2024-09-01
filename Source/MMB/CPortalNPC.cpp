// Fill out your copyright notice in the Description page of Project Settings.


#include "CPortalNPC.h"

void ACPortalNPC::GetTeleportableMaps(TArray<struct FTeleportableMapTableRow*>& Arr)
{
	//if (MapTable == nullptr) return;
	//MapTable->GetAllRows<FTeleportableMapTableRow>(TEXT("GetAllRows"), Arr);
}

void ACPortalNPC::GetTeleportableMaps(TArray<struct FTeleportableMapMonsterTableRow*>& Arr)
{
	if (MapTable == nullptr) return;
	MapTable->GetAllRows<FTeleportableMapMonsterTableRow>(TEXT("GetAllRows"), Arr);
}

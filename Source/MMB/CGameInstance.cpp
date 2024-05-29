// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"

void UCGameInstance::Init()
{
	Super::Init();
	SelectedSaveSlot = -1;
}

void UCGameInstance::Shutdown()
{
	Super::Shutdown();
}

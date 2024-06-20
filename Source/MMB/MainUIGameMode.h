// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PCH.h"
#include "MainUIGameMode.generated.h"

UCLASS()
class MMB_API AMainUIGameMode : public AGameModeBase, public IIItemManager
{
	GENERATED_BODY()
	
	AMainUIGameMode();

	virtual void BeginPlay() override;

	class UDataTable* ItemTable;
	class UCGameInstance* GameInstance;
	UTexture2D* DefaultIconDroppedItem;
	TMap<FString, UTexture2D*> PreLoadedTextureMap;
	TMap<FString, class USoundBase*> PreBGMMap;

public:

	UPROPERTY(EditDefaultsOnly, Category = Zone)
	TSoftObjectPtr<UWorld> LevelToLoad;

	virtual UTexture2D* IconGetter(FString IconAssetName) override;
	virtual class UCInventoryItemData* GetItem(FName ItemRowName, int Count = 1) override;
};

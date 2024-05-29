// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CStaticNPC.h"
#include "CPlayerController.h"
#include "CPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Materials/Material.h"
#include "Slate/SlateBrushAsset.h"
#include "IItemManager.h"
#include "MMBGameModeBase.generated.h"

UCLASS()
class MMB_API AMMBGameModeBase : public AGameModeBase, public IIItemManager
{
	GENERATED_BODY()

	AMMBGameModeBase();

	virtual void BeginPlay() override;
private:
	TArray<UTexture2D*> PreLoadedTextures;
	TArray<UMaterialInstance*> DropItemMaterialsRarity;
	TMap<FString, UTexture2D*> PreLoadedTextureMap;
	//TArray<USlateBrushAsset*> SlateBrushArr;

	class UDataTable* ItemTable;

	class UCGameInstance* GameInstance;
public:

	UPROPERTY(EditDefaultsOnly, Category = Zone)
	TSoftObjectPtr<UWorld> LevelToLoad;

	UTexture2D* GetPreLoadedTexture(int32 e);

	UTexture2D* IconStaff;
	UTexture2D* DefaultIconDroppedItem;

	UClass* GetItemClass(int32 e);
	UMaterialInstance* GetDropItemMaterial(int32 Rarity);
	//FSlateBrush* GetSlateBrush(int32 e);
	
	virtual UTexture2D* IconGetter(FString IconAssetName) override;
	virtual class UCInventoryItemData* GetItem(FName ItemRowName, int Count = 1) override;
};

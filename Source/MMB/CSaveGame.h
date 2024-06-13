// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSaveGame.generated.h"

UCLASS()
class MMB_API UCSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<int32> SavedClearedQuestList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<FName> SavedItemList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<int32> SavedItemListQ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName SavedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName SavedArtifact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName SavedArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SavedGold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName SavedLevel;

	//FString SavedLevel;
};

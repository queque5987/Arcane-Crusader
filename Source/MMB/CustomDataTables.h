// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CustomDataTables.generated.h"

USTRUCT(BlueprintType)
struct FQuestsRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestRecap;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestInitializeIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestRewardIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FString> QuestRequiredClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<int> QuestRequiredQuantity;
};

USTRUCT(BlueprintType)
struct FNPCDialoguesRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText NPCName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText NPCDialogue;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestID;

};

USTRUCT(BlueprintType)
struct FDropTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ItemClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ItemAttackDamage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int ItemPrice;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int ItemTexture;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ItemDropRate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Rarity;
};

USTRUCT(BlueprintType)
struct FTeleportableMapTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Level;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector Pos;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString PreviewSlateBrush;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int RelatedQuestIndex;
};

UCLASS()
class MMB_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
};

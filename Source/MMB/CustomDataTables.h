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
	int QuestDialogueIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestRewardDialogueIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString QuestRecap;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestInitializeIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestRewardIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FString> QuestRequiredClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FString> QuestRequiredClassName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<int> QuestRequiredQuantity;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FName> QuestRewards;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<int> QuestRewardsQuantity;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FString> RequiredQuest;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ClearableNPCClass;

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

	//Deprecated
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int QuestID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_NEXT_POSTLINE;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_YES_POSTLINE;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_NO_POSTLINE;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_SHOP_POSTLINE;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_QUEST_POSTLINE;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_LEAVE_POSTLINE;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int BUTTON_REWARD_POSTLINE;
};

USTRUCT(BlueprintType)
struct FMonsterConfigTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString MonsterClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MonsterTextureArrayIndex;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString MonsterName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString DropTable;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterHP;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MonsterDamage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float MaxWalkSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float FlyAcc;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float VirticalAcc;
};

USTRUCT(BlueprintType)
struct FDropTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ItemCode;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float ItemDropRate;
};

USTRUCT(BlueprintType)
struct FTeleportableMapMonsterTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName DisplayLevelName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 TextureArrayIndex;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Level;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector Pos;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FName> SpawnableMonsters;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<int32> SpawnableMonsterPreviews;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<int32> RelatedQuestIndexs;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float LevelClock;
};

//Deprecated
USTRUCT(BlueprintType)
struct FTeleportableMapTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName DestLevelName;
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
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float LevelClock;
};

USTRUCT(BlueprintType)
struct FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ItemClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ItemName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString IconTexture;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ItemPrice;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ItemDetail;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float AttackDamage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Defence;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float AttackSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Potion_HealPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Rarity;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ItemType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 BulletType;
};

UCLASS()
class MMB_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
};

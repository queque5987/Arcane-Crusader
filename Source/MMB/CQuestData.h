// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomDataTables.h"
#include "CQuestData.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCQuestData : public UObject
{
	GENERATED_BODY()
	UCQuestData(const FObjectInitializer& ObjectInitializer);

	// Row Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString QuestName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString QuestRecap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int QuestDialogueIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int QuestRewardDialogueIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int QuestInitializeIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int QuestRewardIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> RMonsterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<int> RQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class ACStaticNPC* GivenNPC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<FName> QuestRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<FString> RequiredQuest;

	UINT32 QuestState = 0;

	//Deprecated
	//bool bCleared;
public:
	void SetDetails(FQuestsRow* Row);

	// Row Properties Getter Setter
	FString GetQuestName() { return QuestName; }
	void SetQuestName(FString e) { QuestName = e; }
	FString GetQuestRecap() { return QuestRecap; }
	void SetQuestRecap(FString e) { QuestRecap = e; }
	int GetQuestDialogueIndex() { return QuestDialogueIndex; }
	void SetQuestDialogueIndex(int e) { QuestDialogueIndex = e; }
	int GetQuestInitializeIndex() { return QuestInitializeIndex; }
	void SetQuestInitializeIndex(int e) { QuestInitializeIndex = e; }
	int GetQuestRewardIndex() { return QuestRewardIndex; }
	void SetQuestRewardIndex(int e) { QuestRewardIndex = e; }
	TArray<UClass*> GetRMonsterClass() { return RMonsterClass; }
	void SetRMonsterClass(TArray<UClass*> e) { RMonsterClass = e; }
	TArray<int> GetRQuantity() { return RQuantity; }
	void SetRQuantity(TArray<int> e) { RQuantity = e; }
	class ACStaticNPC* GetGivenNPC() { return GivenNPC; }
	void SetGivenNPC(class ACStaticNPC* e) { GivenNPC = e; }
	int GetQuestRewardDialogueIndex() { return QuestRewardDialogueIndex; }
	void SetQuestRewardDialogueIndex(int e) { QuestRewardDialogueIndex = e; }
	TArray<FName> GetQuestRewards() { return QuestRewards; }
	void SetQuestRewards(TArray<FName> e) { QuestRewards = e; }
	TArray<FString> GetRequiredQuest() { return RequiredQuest; }
	void SetRequiredQuest(TArray<FString> e) { RequiredQuest = e; }


	void SetQuestState(UINT32 e) { QuestState = e; }
	UINT32 GetQuestState() { return QuestState; }

	//Deprecated
	//bool GetbCleared() { return bCleared; }
	//void SetbCleared(bool e) { bCleared = e; }
private:
	UClass* GetClassFromPath(FString ClassPath);
};

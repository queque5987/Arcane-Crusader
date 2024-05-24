// Fill out your copyright notice in the Description page of Project Settings.


#include "CQuestData.h"
#include "UObject/ConstructorHelpers.h"

UCQuestData::UCQuestData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCQuestData::SetDetails(FQuestsRow* Row)
{
	QuestName = Row->QuestName;
	QuestRecap = Row->QuestRecap;
	QuestRewardIndex = Row->QuestRewardIndex;
	QuestDialogueIndex = Row->QuestDialogueIndex;
	RMonsterClass = TArray<UClass*>();
	for (FString ClassPath : Row->QuestRequiredClass)
	{
		RMonsterClass.Add(GetClassFromPath(ClassPath));
	}
	RQuantity = Row->QuestRequiredQuantity;
	QuestInitializeIndex = Row->QuestInitializeIndex;
	QuestRewardDialogueIndex = Row->QuestRewardDialogueIndex;
	QuestRewards = Row->QuestRewards;
	RequiredQuest = Row->RequiredQuest;
}

UClass* UCQuestData::GetClassFromPath(FString ClassPath)
{
	return StaticLoadClass(AActor::StaticClass(), nullptr, *ClassPath);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CQuestData.h"
#include "UObject/ConstructorHelpers.h"
#include "FMonsterConfigure.h"
#include "CPotion.h"

UCQuestData::UCQuestData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCQuestData::SetDetails(FQuestsRow* Row)
{
	QuestName = Row->QuestName;
	QuestRecap = Row->QuestRecap;
	QuestRewardIndex = Row->QuestRewardIndex;
	QuestDialogueIndex = Row->QuestDialogueIndex;

	RAction = Row->QuestRequiredAction;
	RMonsterClass = TArray<UClass*>();

	for (FString ClassPath : Row->QuestRequiredClass)
	{
		RMonsterClass.Add(GetClassFromPath(ClassPath));
	}
	RQuantity = Row->QuestRequiredQuantity;
	RClassName = Row->QuestRequiredClassName;

	QuestInitializeIndex = Row->QuestInitializeIndex;
	QuestRewardDialogueIndex = Row->QuestRewardDialogueIndex;
	QuestRewards = Row->QuestRewards;
	RequiredQuest = Row->RequiredQuest;
	QuestRewardsQuantity = Row->QuestRewardsQuantity;

	GivenNPC = GetClassFromPath(Row->ClearableNPCClass);
}

void UCQuestData::SetQuestByMonsterConfig(UFMonsterConfigure* MonsterConfig)
{
	if (MonsterConfig->GetMonsterClass() == nullptr) return;
	//QuestName = MonsterConfig->GetMonsterClass()->GetName();
	//QuestRecap = 
}

UClass* UCQuestData::GetClassFromPath(FString ClassPath)
{
	return StaticLoadClass(AActor::StaticClass(), nullptr, *ClassPath);
}

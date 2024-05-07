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
	QuestReward = nullptr; //Row->QuestReward;
	QuestType = Row->QuestType;
	RMonsterClass = TArray<UClass*>();
	for (FString ClassPath : Row->QuestRequiredClass)
	{
		RMonsterClass.Add(GetClassFromPath(ClassPath));
	}
	RQuantity = Row->QuestRequiredQuantity;
}

UClass* UCQuestData::GetClassFromPath(FString ClassPath)
{
	return StaticLoadClass(AActor::StaticClass(), nullptr, *ClassPath);
}

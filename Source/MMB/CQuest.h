// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CQuestData.h"
#include "PCH.h"
#include "CQuest.generated.h"

UCLASS()
class MMB_API UCQuest : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestRecap;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> QuestBG;

	bool RefreshQuestRecap(UObject* AchievedObject = nullptr, int AchievedActionType = 0);
	bool RefreshQuestRecap(UClass* AchievedObjectClass, int AchievedActionType = 0);
	bool ManualAchieveQuestRecap(int AchievedObjectClassIndex);
	FString GetQuestName() { return QuestNameString; }
	bool IsCleared() { return bCleared; };
	int GetQuestRewardIndex() { 
		UE_LOG(LogTemp, Log, TEXT("Quest Reward Index : %d"), QuestRewardIndex);
		return QuestRewardIndex; }
	int GetQuestInitializeIndex() { return QuestInitializeIndex; }
	UClass* GetGivenNPC() { return GivenNPC; };
	void SetGivenNPC(UClass* NPC) { GivenNPC = NPC; };
protected:
	//UObject* QuestData;
	UCQuestData* QuestData;
	FString QuestRecapString;
	FString QuestNameString;
	bool bCleared;
	UClass* GivenNPC;
	TArray<UClass*> RequiredClasses;
	TArray<FString> RequiredClassNames;
	TArray<int> AcquiredQuantities;
	TArray<int> RequiredQuantities;
	TArray<int> RequiredActions;
	int QuestRewardIndex;
	int QuestRewardDialogueIndex;
	int QuestInitializeIndex;
private:
	FLinearColor QualifiedColor;
};

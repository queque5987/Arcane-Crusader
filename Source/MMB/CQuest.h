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

/**
 * 
 */
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

	void RefreshQuestRecap(UClass* AchievedClass = nullptr);
	FString GetQuestName() { return QuestNameString; }
	bool IsCleared() { return bCleared; };
protected:
	UObject* QuestData;
	FString QuestRecapString;
	FString QuestNameString;
	bool bCleared;
	TArray<UClass*> RequiredClasses;
	TArray<int> AcquiredQuantities;
	TArray<int> RequiredQuantities;
private:
	FLinearColor QualifiedColor;
};

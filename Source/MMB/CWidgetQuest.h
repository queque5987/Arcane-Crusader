// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CQuestData.h"
#include "PCH.h"
#include "CWidgetQuest.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCWidgetQuest : public UUserWidget, public IUserObjectListEntry
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
public:
	void RefreshQuestRecap(ACPlayerController* PCC, UClass* AchievedClass = nullptr);
	FString GetQuestName() { return QuestNameString; }
	bool IsCleared() { return bCleared; };
	
};

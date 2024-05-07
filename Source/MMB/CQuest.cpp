// Fill out your copyright notice in the Description page of Project Settings.


#include "CQuest.h"

void UCQuest::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	bCleared = false;
	QualifiedColor = FLinearColor(0.f, 1.0f, 0.f, 0.4f);
	QuestData = ListItemObject;

	if (UCQuestData* QD = Cast<UCQuestData>(QuestData))
	{
		QuestNameString = QD->GetQuestName();
		QuestName->SetText(FText::FromString(QuestNameString));
		RequiredClasses = QD->GetRMonsterClass();
		AcquiredQuantities.Init(0, RequiredClasses.Num());
		RequiredQuantities = QD->GetRQuantity();
		QuestRecapString = QD->GetQuestRecap();
		RefreshQuestRecap();
	}

	//UE_LOG(LogTemp, Log, TEXT("QuestData Loaded"));
}

void UCQuest::RefreshQuestRecap(UClass* AchievedClass)
{
	FString Recap = QuestRecapString + "\n";
	int Achieved = RequiredClasses.Num();
	for (int i = 0; i < RequiredClasses.Num(); i++)
	{
		if (AchievedClass != nullptr && RequiredClasses[i] == AchievedClass)
		{
			AcquiredQuantities[i] += 1;
		}

		Recap += "\n" + RequiredClasses[i]->GetName() +
			" " + FString::FromInt(AcquiredQuantities[i]) +
			" / " + FString::FromInt(RequiredQuantities[i]);
		if (AcquiredQuantities[i] >= RequiredQuantities[i]) Achieved--;
	}
	QuestRecap->SetText(FText::FromString(Recap));
	if (Achieved <= 0)
	{
		QuestBG->SetColorAndOpacity(QualifiedColor);
		bCleared = true;
	}
}

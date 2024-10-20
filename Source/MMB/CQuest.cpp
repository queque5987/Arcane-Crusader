// Fill out your copyright notice in the Description page of Project Settings.


#include "CQuest.h"

void UCQuest::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	bCleared = false;
	QuestBG->SetColorAndOpacity(FLinearColor(1.f, 0.0f, 0.f, 0.4f));
	QualifiedColor = FLinearColor(0.f, 1.0f, 0.f, 0.4f);

	if (UCQuestData* QD = Cast<UCQuestData>(ListItemObject))
	{
		QuestData = QD;
		QuestNameString = QD->GetQuestName();
		QuestName->SetText(FText::FromString(QuestNameString));
		RequiredClasses = QD->GetRMonsterClass();
		AcquiredQuantities.Init(0, RequiredClasses.Num());
		RequiredQuantities = QD->GetRQuantity();
		RequiredActions = QD->GetRAction();
		QuestRecapString = QD->GetQuestRecap();
		QuestRewardIndex = QD->GetQuestRewardIndex();
		QuestInitializeIndex = QD->GetQuestInitializeIndex();
		QuestRewardDialogueIndex = QD->GetQuestRewardDialogueIndex();
		GivenNPC = QD->GetGivenNPC();
		RequiredClassNames = QD->GetRClassName();
		RefreshQuestRecap();
	}

	//UE_LOG(LogTemp, Log, TEXT("QuestData Loaded"));
}

bool UCQuest::RefreshQuestRecap(UObject* AchievedObject, int AchievedActionType)
{
	FString Recap = QuestRecapString + "\n";
	int Achieved = RequiredClasses.Num();
	for (int i = 0; i < RequiredClasses.Num(); i++)
	{
		if (AchievedObject != nullptr)
		{
			if (AchievedObject->IsA(RequiredClasses[i]))
			{
				AcquiredQuantities[i] += 1;
			}
		}

		//Recap += "\n" + RequiredClasses[i]->GetName() +
		Recap += "\n" + RequiredClassNames[i] +
			" " + FString::FromInt(AcquiredQuantities[i]) +
			" / " + FString::FromInt(RequiredQuantities[i]);
		if (AcquiredQuantities[i] >= RequiredQuantities[i]) Achieved--;
	}
	QuestRecap->SetText(FText::FromString(Recap));
	if (Achieved <= 0)
	{
		QuestBG->SetColorAndOpacity(QualifiedColor);
		bCleared = true;
		//if (QuestData != nullptr) QuestData->SetbCleared(bCleared);
	}
	return bCleared;
}

bool UCQuest::RefreshQuestRecap(UClass* AchievedObjectClass, int AchievedActionType)
{
	FString Recap = QuestRecapString + "\n";
	int Achieved = RequiredClasses.Num();
	for (int i = 0; i < RequiredClasses.Num(); i++)
	{
		if (AchievedObjectClass != nullptr)
		{
			//UE_LOG(LogTemp, Log, TEXT("UCQuest::RefreshQuestRecap : %s / %s"), *AchievedObjectClass->GetName(), *RequiredClasses[i]->GetName());
			if (RequiredActions[i] == AchievedActionType && AchievedObjectClass == RequiredClasses[i])
			{
				AcquiredQuantities[i] += 1;
			}
		}

		Recap += "\n" + RequiredClassNames[i] +
			" " + FString::FromInt(AcquiredQuantities[i]) +
			" / " + FString::FromInt(RequiredQuantities[i]);
		if (AcquiredQuantities[i] >= RequiredQuantities[i]) Achieved--;
	}
	QuestRecap->SetText(FText::FromString(Recap));
	if (Achieved <= 0)
	{
		QuestBG->SetColorAndOpacity(QualifiedColor);
		bCleared = true;
		//if (QuestData != nullptr) QuestData->SetbCleared(bCleared);
	}
	return bCleared;
}

bool UCQuest::ManualAchieveQuestRecap(int AchievedObjectClassIndex)
{
	FString Recap = QuestRecapString + "\n";
	if (!RequiredClasses.IsValidIndex(AchievedObjectClassIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("ManualAchieveQuestRecap : Invalid Index"));
		return false;
	}
	int Achieved = RequiredClasses.Num();

	for (int i = 0; i < RequiredClasses.Num(); i++)
	{
		if (i == AchievedObjectClassIndex)
		{
			AcquiredQuantities[i] += 1;
		}

		Recap += "\n" + RequiredClassNames[i] +
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
	return bCleared;
}

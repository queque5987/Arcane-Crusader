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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString QuestName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString QuestRecap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int QuestType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UObject* QuestReward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> RMonsterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<int> RQuantity;
public:
	void SetDetails(FQuestsRow* Row);

	FString GetQuestName() { return QuestName; }
	void SetQuestName(FString e) { QuestName = e; }
	FString GetQuestRecap() { return QuestRecap; }
	void SetQuestRecap(FString e) { QuestRecap = e; }
	int GetQuestType() { return QuestType; }
	void SetQuestType(int e) { QuestType = e; }
	UObject* GetQuestReward() { return QuestReward; }
	void SetQuestReward(UObject* e) { QuestReward = e; }
	TArray<UClass*> GetRMonsterClass() { return RMonsterClass; }
	void SetRMonsterClass(TArray<UClass*> e) { RMonsterClass = e; }
	TArray<int> GetRQuantity() { return RQuantity; }
	void SetRQuantity(TArray<int> e) { RQuantity = e; }

private:
	UClass* GetClassFromPath(FString ClassPath);
};

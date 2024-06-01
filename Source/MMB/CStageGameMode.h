// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMBGameModeBase.h"
#include "CStageGameMode.generated.h"

UCLASS()
class MMB_API ACStageGameMode : public AMMBGameModeBase
{
	GENERATED_BODY()

	ACStageGameMode();

	virtual void BeginPlay() override;


	class UDataTable* QuestTable;

public:
	struct FQuestsRow* GetQuestbyIndex(int32 QuestIdx);
};

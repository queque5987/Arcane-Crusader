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

	virtual void Tick(float DeltaSeconds) override;

	class UDataTable* QuestTable;
	class ADirectionalLight* DirectionalLight;

	float LevelClock;
	float FullDaySecond = 600.f;
	float MaxClock = 24.f * 60.f;
public:
	struct FQuestsRow* GetQuestbyIndex(int32 QuestIdx);
	void InitLevelClock(float fClock);
	float GetCurrentLevelClock() { return LevelClock; }
};

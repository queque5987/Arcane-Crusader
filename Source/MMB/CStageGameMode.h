// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMBGameModeBase.h"
#include "IStageMaterialManager.h"
#include "CStageGameMode.generated.h"

DECLARE_DELEGATE(FPlayerDodged);
DECLARE_DELEGATE(FPlayerDodgedEnd);

UCLASS()
class MMB_API ACStageGameMode : public AMMBGameModeBase, public IIStageMaterialManager
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

	class UMaterialParameterCollectionInstance* MPC_GlobalPostProcessVolume;

	float PostProcessRadius;
	float PostProcessMaxRadius;
	bool bPostProcessZoom;

	TArray<class UParticleSystemComponent*> SpawnedParticleComponents;
	TArray<float> SpawnedParticleLifeSpans;

public:
	FPlayerDodged PlayerDodged;
	FPlayerDodgedEnd PlayerDodgedEnd;

	virtual struct FQuestsRow* GetQuestbyIndex(int32 QuestIdx) override;
	void InitLevelClock(float fClock);
	float GetCurrentLevelClock() { return LevelClock; }

	virtual void UpdatePlayerCharacterPos(FVector Pos) override;
	virtual void UpdateRadius(float e) override;
	virtual float GetPostProcessRadius() override;
	virtual void PostProcessZoom(bool IsStart, FVector ZoomPos) override;
	virtual void ExecutePlayerDodgedEvent() override;
	virtual void ExecutePlayerDodgedEndEvent() override;

	virtual void SpawnParticle(class UParticleSystem* SpawnParticle, float LifeSpan, FVector Location, FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.f), class USceneComponent* ToAttachComponent = nullptr) override;

};

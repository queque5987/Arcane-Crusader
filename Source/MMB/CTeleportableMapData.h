// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CTeleportableMapData.generated.h"

UCLASS()
class MMB_API UCTeleportableMapData : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName DestLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> DestLevel;
	//UWorld* DestLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FVector DestLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int ArrIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString PreviewSlateBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int RelatedQuestIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float StartLevelClock;
public:
	TSoftObjectPtr<UWorld> GetDestLevel() { return DestLevel; }
	void SetDestLevel(TSoftObjectPtr<UWorld> e) { DestLevel = e; }
	FVector GetDestLocation() { return DestLocation; }
	void SetDestLocation(FVector e) { DestLocation = e; }
	FName GetLevelName() { return LevelName; }
	void SetLevelName(FName e) { LevelName = e; }
	FName GetDestLevelName() { return DestLevelName; }
	void SetDestLevelName(FName e) { DestLevelName = e; }
	int GetArrIndex() { return ArrIndex; }
	void SetArrIndex(int e) { ArrIndex = e; }
	FString GetPreviewSlateBrush() { return PreviewSlateBrush; }
	void SetPreviewSlateBrush(FString e) { PreviewSlateBrush = e; }
	int GetRelatedQuestIndex() { return RelatedQuestIndex; }
	void SetRelatedQuestIndex(int e) { RelatedQuestIndex = e; }
	float GetStartLevelClock() { return StartLevelClock; }
	void SetStartLevelClock(float e) { StartLevelClock = e; }

};

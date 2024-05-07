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
	FName DestLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UWorld* DestLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FVector DestLocation;

public:
	UWorld* GetDestLevel() { return DestLevel; }
	void SetDestLevel(UWorld* e) { DestLevel = e; }
	FVector GetDestLocation() { return DestLocation; }
	void SetDestLocation(FVector e) { DestLocation = e; }
	FName GetDestLevelName() { return DestLevelName; }
	void SetDestLevelName(FName e) { DestLevelName = e; }
};

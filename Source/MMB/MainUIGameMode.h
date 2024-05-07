// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PCH.h"
#include "MainUIGameMode.generated.h"

UCLASS()
class MMB_API AMainUIGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AMainUIGameMode();

	//virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = Zone)
	TSoftObjectPtr<UWorld> LevelToLoad;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyAIController.h"
#include "CEnemyAIController_Barghest.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API ACEnemyAIController_Barghest : public ACEnemyAIController
{
	GENERATED_BODY()
	ACEnemyAIController_Barghest(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyAIController.h"
#include "CEnemyAIController_NM.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API ACEnemyAIController_NM : public ACEnemyAIController
{
	GENERATED_BODY()
	ACEnemyAIController_NM(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;
	
};

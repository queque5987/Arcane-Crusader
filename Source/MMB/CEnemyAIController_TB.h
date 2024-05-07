// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyAIController.h"
#include "IFlyMonster_AIController.h"
#include "CEnemyAIController_TB.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API ACEnemyAIController_TB : public ACEnemyAIController, public IIFlyMonster_AIController
{
	GENERATED_BODY()
	ACEnemyAIController_TB(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;
public:
	void SwitchFlyMode();
	bool GetIsOnAir();
	static const FName bIsOnAir;

public:
	virtual FVector GetFlyPatrolPos() override;
private:
	class UAISenseConfig_Sight* FlyingSightConfig;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskFlyToward.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTTaskFlyToward : public UBTTaskNode
{
	GENERATED_BODY()

	UCBTTaskFlyToward();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float AcceptableRadius = 50.f;
};

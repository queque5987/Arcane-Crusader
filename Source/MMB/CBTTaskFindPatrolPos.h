// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskFindPatrolPos.generated.h"

UCLASS()
class MMB_API UCBTTaskFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskFindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

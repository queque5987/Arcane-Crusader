// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "CBTTask_Move_Patrol.generated.h"

UCLASS()
class MMB_API UCBTTask_Move_Patrol : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	UCBTTask_Move_Patrol(const FObjectInitializer& ObjectInitializer);
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

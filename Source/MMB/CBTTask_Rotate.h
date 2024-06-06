// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CBTTask_Rotate.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTTask_Rotate : public UBTTask_BlackboardBase// : public UBTTaskNode
{
	GENERATED_BODY()
	UCBTTask_Rotate();

	UPROPERTY(Category = Blackboard, EditAnywhere, meta = (EditCondition = "bObserveBlackboardValue", DisplayAfter = "bObserveBlackboardValue"))
	float RotateSpeed;

	UPROPERTY(Category = Blackboard, EditAnywhere, meta = (EditCondition = "bObserveBlackboardValue", DisplayAfter = "bObserveBlackboardValue"))
	float RotateBoundary;
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};

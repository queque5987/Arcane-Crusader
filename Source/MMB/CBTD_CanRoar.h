// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CEnemyAIController.h"
#include "CBTD_CanRoar.generated.h"
UCLASS()
class MMB_API UCBTD_CanRoar : public UBTDecorator
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

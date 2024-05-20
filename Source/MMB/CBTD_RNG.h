// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTD_RNG.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTD_RNG : public UBTDecorator
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float RandMax;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};

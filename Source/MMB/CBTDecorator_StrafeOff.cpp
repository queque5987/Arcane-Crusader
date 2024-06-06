// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTDecorator_StrafeOff.h"
#include "AIController.h"
#include "IEnemyBBState.h"

bool UCBTDecorator_StrafeOff::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	IIEnemyBBState* BBState = Cast<IIEnemyBBState>(OwnerComp.GetAIOwner());
	if (BBState == nullptr) return false;
	BBState->SetIsStrafe(0.f);
	return true;
}

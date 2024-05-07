// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTD_CanRoar.h"

bool UCBTD_CanRoar::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	if (ACEnemyAIController* ECC = Cast<ACEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		return ECC->GetCanRoar();
	}
	return false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTD_RNG.h"
#include "AIController.h"
#include "IEnemyBBState.h"

bool UCBTD_RNG::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	IIEnemyBBState* EC = Cast<IIEnemyBBState>(OwnerComp.GetAIOwner());
	if (EC == nullptr) return false;
	
	EC->SetRNG(FMath::FRandRange(0.f, RandMax));
	return true;
}

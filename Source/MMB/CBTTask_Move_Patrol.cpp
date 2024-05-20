// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTask_Move_Patrol.h"
#include "AIController.h"
#include "IEnemyBBState.h"

UCBTTask_Move_Patrol::UCBTTask_Move_Patrol(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

EBTNodeResult::Type UCBTTask_Move_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type rtn = Super::ExecuteTask(OwnerComp, NodeMemory);

	IIEnemyBBState* EnemyBB = Cast<IIEnemyBBState>(OwnerComp.GetAIOwner());
	if (EnemyBB == nullptr) return EBTNodeResult::Failed;

	bool bSeePlayer = EnemyBB->GetbSeePlayer();
	if (bSeePlayer)
	{
		return Super::AbortTask(OwnerComp, NodeMemory);
	}
	return rtn;
}

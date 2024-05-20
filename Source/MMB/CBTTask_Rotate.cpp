// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTask_Rotate.h"
#include "IEnemyBBState.h"

UCBTTask_Rotate::UCBTTask_Rotate()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTask_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//IIEnemyBBState* EnemyAIController = Cast<IIEnemyBBState>(OwnerComp.GetAIOwner());
	//FVector PlayerPos = EnemyAIController->GetPlayerPos();
	//AActor* EnemyActor = OwnerComp.GetOwner();
	//FVector EnemyPos = EnemyActor->GetActorLocation();
	//FVector EnemyForEnemyActor->GetActorForwardVector();
	return EBTNodeResult::Type();
}

void UCBTTask_Rotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}

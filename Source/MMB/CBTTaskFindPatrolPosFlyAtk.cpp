// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskFindPatrolPosFlyAtk.h"
#include "CEnemy_TerrorBringer.h"

UCBTTaskFindPatrolPosFlyAtk::UCBTTaskFindPatrolPosFlyAtk()
{
	NodeName = TEXT("FlyAttack");
}

EBTNodeResult::Type UCBTTaskFindPatrolPosFlyAtk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return EBTNodeResult::Failed;
	ACEnemy_TerrorBringer* TB = Cast<ACEnemy_TerrorBringer>(ControllingPawn);
	if (!IsValid(TB)) return EBTNodeResult::Failed;
	return TB->DoFlyFireAttack.ExecuteIfBound() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;



	//IIFlyMonster* IFly = Cast<IIFlyMonster>(OwnerComp.GetAIOwner()->GetCharacter());
	//if (IFly == nullptr) return EBTNodeResult::Failed;
	//float CurrAltitude = IFly->GetCurrentAltitude();

	//UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	//if (NavSystem == nullptr) return EBTNodeResult::Failed;

	////FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ACEnemyAIController::HomePosKey);
	////FNavLocation NextPatrol;

	////if (NavSystem->GetRandomPointInNavigableRadius(Origin, 3000.f, NextPatrol))
	////{
	////	NextPatrol.Location += FVector(0.f, 0.f, CurrAltitude);
	////	OwnerComp.GetBlackboardComponent()->SetValueAsVector(ACEnemyAIController::PatrolPosKey, NextPatrol.Location);

	////	DrawDebugSphere(GetWorld(), NextPatrol.Location, 500.f, 32, FColor::Blue, false, 5.f);
	////	return EBTNodeResult::Succeeded;
	////}
}

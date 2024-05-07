// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskFlyToward.h"
#include "IFlyMonster.h"
#include "IFlyMonster_AIController.h"
#include "CEnemyAIController_TB.h"
#include "CEnemy_TerrorBringer.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskFlyToward::UCBTTaskFlyToward() : Super()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskFlyToward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return EBTNodeResult::Failed;

	IIFlyMonster_AIController* IFlyCtrl = Cast<IIFlyMonster_AIController>(OwnerComp.GetAIOwner());
	if (IFlyCtrl == nullptr) return EBTNodeResult::Failed;
	FVector FlyDestination = IFlyCtrl->GetFlyPatrolPos();

	return (FVector::Distance(ControllingPawn->GetActorLocation(), FlyDestination) > AcceptableRadius) ? EBTNodeResult::InProgress : EBTNodeResult::Succeeded;
}

void UCBTTaskFlyToward::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//UE_LOG(LogTemp, Log, TEXT("Tick Task"));
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return;

	IIFlyMonster_AIController* IFlyCtrl = Cast<IIFlyMonster_AIController>(OwnerComp.GetAIOwner());
	if (IFlyCtrl == nullptr) return;
	FVector FlyDestination = IFlyCtrl->GetFlyPatrolPos();

	IIFlyMonster* IFly = Cast<IIFlyMonster>(OwnerComp.GetAIOwner()->GetCharacter());
	if (IFly == nullptr) return;

	if (IFly->FlyTo(FlyDestination, DeltaSeconds, AcceptableRadius))
	{
		FinishLatentAbort(OwnerComp);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	//UE_LOG(LogTemp, Log, TEXT("From %s To %s : %f"), *ControllingPawn->GetActorLocation().ToString(), *FlyDestination.ToString(), FVector::Distance(ControllingPawn->GetActorLocation(), FlyDestination));
	//if (FVector::Distance(ControllingPawn->GetActorLocation(), FlyDestination) < AcceptableRadius)
	//{
	//	FinishLatentAbort(OwnerComp);
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	//AbortTask(OwnerComp, NodeMemory);
	//}
}

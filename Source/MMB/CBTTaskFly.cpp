// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskFly.h"
#include "CEnemyAIController.h"
#include "CEnemyAIController_TB.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UCBTTaskFly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return EBTNodeResult::Failed;
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(ControllingPawn);
	if (!IsValid(EC)) return EBTNodeResult::Failed;
	ACEnemyAIController* ECC = Cast<ACEnemyAIController>(EC->GetController());
	if (!IsValid(ECC)) return EBTNodeResult::Failed;

	DoFly(ECC);

	return EBTNodeResult::Failed;
}

void UCBTTaskFly::DoFly(ACEnemyAIController* ECC)
{
	if (ACEnemyAIController_TB* ACC_TB = Cast<ACEnemyAIController_TB>(ECC))
	{
		UE_LOG(LogTemp, Log, TEXT("Switch Fly Mode"));
		ACC_TB->SwitchFlyMode();
	}
}

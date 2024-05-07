// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskEncountered.h"
#include "CEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskEncountered::UCBTTaskEncountered()
{
	NodeName = TEXT("Encountered");
}

EBTNodeResult::Type UCBTTaskEncountered::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return EBTNodeResult::Failed;
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(ControllingPawn);
	if (!IsValid(EC)) return EBTNodeResult::Failed;
	ACEnemyAIController* ECC = Cast<ACEnemyAIController>(EC->GetController());
	if (!IsValid(ECC)) return EBTNodeResult::Failed;
	//ECC->SetbBusy(true);
	ECC->SetCanRoar(false);
	ECC->SetRoarCooldownTimer();
	EC->DoRoar.ExecuteIfBound();
	//GetWorld()->GetTimerManager().SetTimer(ECC->RoarTimerHandle, this, &ACEnemyAIController::RoarCooldownTimer, ECC->GetRoarCooldown());
	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTask_Enemy_ComputeNextAction.h"
#include "BehaviorTree/BlackboardData.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IEnemyAITactics.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UCBTTask_Enemy_ComputeNextAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Log, TEXT("EBTNodeResult::Type UCBTTask_Enemy_ComputeNextAction : %s"), *BlackboardKey.SelectedKeyName.ToString());
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr) return EBTNodeResult::Failed;
	IIEnemyAITactics* EnemyAITactics = Cast<IIEnemyAITactics>(AIController);
	if (EnemyAITactics == nullptr) return EBTNodeResult::Failed;
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	if (BBComponent == nullptr) return EBTNodeResult::Failed;
	ACharacter* E = AIController->GetCharacter();
	if (E == nullptr) return EBTNodeResult::Failed;

	bool PlayerAttacking = EnemyAITactics->IsPlayerAttacking();
	FVector PlayerLoc = EnemyAITactics->GetPlayerLocation();
	float PlayerDist = FVector::Dist(E->GetActorLocation(), PlayerLoc);
	FVector PlayerVelocity = EnemyAITactics->GetPlayerVelocity();

	FVector TargetVector = (PlayerLoc - E->GetActorLocation()).GetSafeNormal();
	FVector ForwardVector = E->GetActorForwardVector();
	FVector RightVector = E->GetActorRightVector();
	int NextActIdx = 0;
	bool IsPlayerInRight = FVector::DotProduct(TargetVector, RightVector) >= 0.f ? true : false;

	double theta = FMath::Abs(FMath::Acos(FVector::DotProduct(TargetVector, ForwardVector)));
	
	double R = FMath::RandRange(0.f, 100.f);
	//UE_LOG(LogTemp, Log, TEXT("UCBTTask_Enemy_ComputeNextAction : %f"), R);

	if (EnemyAITactics->IsEnemyBusy()) NextActIdx = -1;
	else if (theta > 0.8f) // To Much Angle
	{
		NextActIdx = IsPlayerInRight ? 4 : 5;	// Turn L or R
	}
	else if (PlayerDist > 1000.f)
	{
		if (PlayerDist > 1500.f)	// Too Far 1500~
		{
			if (R > 30.f) NextActIdx = 6;	// FireBall 70%
			else NextActIdx = -1;	// Move To Player 30%
		}
		else // Not Too Far 1000~1500
		{
			if (R > 40.f) NextActIdx = 7;	// BreathFire 60%
			else
			{
				if (R > 10.f) NextActIdx = 6;	// FireBall 30%
				else NextActIdx = -1;	// Move To Player 10%
			}
		}
	}
	else if (PlayerDist > 500.f) // Far Dist Attack 500~1000
	{
		if (R > 20.f) NextActIdx = 3;							// Combo Claw 80%
		else NextActIdx = 0;	// Bite Grasp 20%
	}
	else if (PlayerAttacking)
	{
		NextActIdx = IsPlayerInRight ? 1 : 2;	// Catch Player Attack Motion L or R
	}
	else
	{
		if (R > 50.f) NextActIdx = 0;								// Bite Grasp 50%
		else if (R > 30.f) NextActIdx = IsPlayerInRight ? 1 : 2;	// Quick Scratch 20%
		else NextActIdx = 3;										// Combo Claw 30%
	}

	BBComponent->SetValueAsInt(GetSelectedBlackboardKey(), NextActIdx);
	return EBTNodeResult::Succeeded;
}

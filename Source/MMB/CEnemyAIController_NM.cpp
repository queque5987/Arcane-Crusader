// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAIController_NM.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ACEnemyAIController_NM::ACEnemyAIController_NM(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTAssetFinder(TEXT("/Game/Enemy/NightMare/AIController/BT_Enemy_Nightmare.BT_Enemy_Nightmare"));
	ConstructorHelpers::FObjectFinder<UBlackboardData>BBAssetFinder(TEXT("/Game/Enemy/NightMare/AIController/BB_Enemy.BB_Enemy"));
	if (BTAssetFinder.Succeeded())
	{
		BTAsset = BTAssetFinder.Object;
	}
	if (BBAssetFinder.Succeeded())
	{
		BBAsset = BBAssetFinder.Object;
	}
}

void ACEnemyAIController_NM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BB = Blackboard;
	if (UseBlackboard(BBAsset, BB))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("AIController coudn't run behavior tree!"));
		}
	}
}

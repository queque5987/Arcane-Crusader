#include "CEnemyAIController_Barghest.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ACEnemyAIController_Barghest::ACEnemyAIController_Barghest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTAssetFinder(TEXT("/Game/Enemy/Barghest/AIController/BT_Barghest"));
	ConstructorHelpers::FObjectFinder<UBlackboardData>BBAssetFinder(TEXT("/Game/Enemy/Barghest/AIController/BB_Barghest"));
	if (BTAssetFinder.Succeeded())
	{
		BTAsset = BTAssetFinder.Object;
	}
	if (BBAssetFinder.Succeeded())
	{
		BBAsset = BBAssetFinder.Object;
	}
}

void ACEnemyAIController_Barghest::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BB = Blackboard;
	if (UseBlackboard(BBAsset, BB))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Error, TEXT("AIController coudn't run behavior tree!"));
		}
	}
}

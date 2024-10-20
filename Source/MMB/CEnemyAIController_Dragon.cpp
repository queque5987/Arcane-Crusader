#include "CEnemyAIController_Dragon.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IEnemyStateManager.h"

ACEnemyAIController_Dragon::ACEnemyAIController_Dragon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTAssetFinder(TEXT("/Game/Enemy/MountainDragon/AI/BT_MountainDragon"));
	ConstructorHelpers::FObjectFinder<UBlackboardData>BBAssetFinder(TEXT("/Game/Enemy/NightMare/AIController/BB_Enemy"));
	if (BTAssetFinder.Succeeded())
	{
		BTAsset = BTAssetFinder.Object;
	}
	if (BBAssetFinder.Succeeded())
	{
		BBAsset = BBAssetFinder.Object;
	}
	LastMoveTimeSec = 0.f;
}

void ACEnemyAIController_Dragon::OnPossess(APawn* InPawn)
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
	ESM = Cast<IIEnemyStateManager>(InPawn);
}

void ACEnemyAIController_Dragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ESM == nullptr) return;
	ESM->SetWalkSpeed(GetWorld()->GetTimeSeconds() < LastMoveTimeSec ? 
		ESM->GetWalkSpeed() + (ESM->GetMaxSpeed() - ESM->GetDefaultSpeed()) / ESM->GetMaxSpeedReachSec() * DeltaTime :
		ESM->GetDefaultSpeed()
	);
}

FPathFollowingRequestResult ACEnemyAIController_Dragon::MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath)
{
	if (ESM == nullptr || ESM->GetbAttacking()) return FPathFollowingRequestResult();

	Super::MoveTo(MoveRequest, OutPath);
	
	UE_LOG(LogTemp, Log, TEXT("ACEnemyAIController_Dragon : Move To Called - %f"), GetWorld()->GetTimeSeconds());
	LastMoveTimeSec = GetWorld()->GetTimeSeconds() + 0.5f;
	return FPathFollowingRequestResult();
}

bool ACEnemyAIController_Dragon::IsEnemyBusy()
{
	if (ESM == nullptr) return false;
	return ESM->IsBusy();
}

#pragma once

#include "CoreMinimal.h"
#include "CEnemyAIController.h"
#include "IEnemyAITactics.h"
#include "CEnemyAIController_Dragon.generated.h"

UCLASS()
class MMB_API ACEnemyAIController_Dragon : public ACEnemyAIController
{
	GENERATED_BODY()
	
	ACEnemyAIController_Dragon(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;

	class IIEnemyStateManager* ESM;

	double LastMoveTimeSec;
public:
	virtual void Tick(float DeltaTime) override;

	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr) override;
	virtual bool IsEnemyBusy() override;

};

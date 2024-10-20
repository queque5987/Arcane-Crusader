#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyStateManager.generated.h"

UINTERFACE(MinimalAPI)
class UIEnemyStateManager : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIEnemyStateManager
{
	GENERATED_BODY()

public:
	virtual bool GetbAttacking() { return false; };
	virtual bool GetHostile() { return false; };
	virtual bool IsBusy() { return false; };

	virtual ACharacter* GetDealingPlayer() { return nullptr; }

	virtual bool IsStartedToFall() { return false; };
	virtual void FreeFall_Init() {};
	virtual void FreeFall() {};
	virtual void Land() {};
	virtual void SetPlayingSequence(bool e) {};
	
	virtual void SpitFireBall(bool bFireImmediate) {};

	virtual bool AttackHitCheck(int AttackType = 0, float DamageScale = 0.f) { return false; };
	virtual void DoAttack(int32 AttackType) {};
	virtual void BiteGraspPlayer() {};
	virtual void BiteGraspEndPlayer() {};

	virtual void SetWalkSpeed(float e) {};
	virtual float GetWalkSpeed() { return 0.f; };
	virtual float GetMaxSpeed() { return 0.f; };
	virtual float GetDefaultSpeed() { return 0.f; };
	virtual float GetMaxSpeedReachSec() { return 0.f; };
};

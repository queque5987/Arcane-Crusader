#pragma once

#include "CoreMinimal.h"
#include "CEnemyCharacter.h"
#include "IFlyMonster.h"
#include "CEnemy_Dragon.generated.h"

DECLARE_DELEGATE(FFall)
DECLARE_DELEGATE(FStationaryToFall)
DECLARE_DELEGATE(FFallToStationary)
DECLARE_DELEGATE(FStationaryToLand)
DECLARE_DELEGATE(FClawComboAttack)
DECLARE_DELEGATE(FLClawAttack)
DECLARE_DELEGATE(FRClawAttack)
DECLARE_DELEGATE(FBiteAttack)
DECLARE_DELEGATE(FBiteGrasp)
DECLARE_DELEGATE(FFireBallAttack)
DECLARE_DELEGATE(FFireBreathAttack)
DECLARE_DELEGATE(FTurnL)
DECLARE_DELEGATE(FTurnR)

DECLARE_DELEGATE_OneParam(FSetPlayingSequence, bool)

UCLASS()
class MMB_API ACEnemy_Dragon : public ACEnemyCharacter, public IIFlyMonster
{
	GENERATED_BODY()

	ACEnemy_Dragon();

public:
	FSetPlayingSequence Delegate_SetPlayingSequence;
	FFall Delegate_Fall;
	FStationaryToFall Delegate_StationaryToFall;
	FFallToStationary Delegate_FallToStationary;
	FStationaryToLand Delegate_StationaryToLand;

	FClawComboAttack Delegate_ClawComboAttack;
	FLClawAttack Delegate_LClawAttack;
	FRClawAttack Delegate_RClawAttack;
	FBiteAttack Delegate_BiteAttack;
	FBiteGrasp Delegate_BiteGrasp;
	FFireBallAttack	Delegate_FireBallAttack;
	FFireBreathAttack Delegate_FireBreathAttack;
	FTurnL Delegate_TurnLeft;
	FTurnR Delegate_TurnRight;

	virtual void DoAttack(int32 AttackType) override;

	virtual void BiteGraspPlayer() override;
	virtual void BiteGraspEndPlayer() override;

	virtual bool IsStartedToFall() override;
	virtual void FreeFall_Init() override;
	virtual void FreeFall() override;
	virtual void Land() override;
	virtual void SetPlayingSequence(bool e) override;

	virtual void PostInitializeComponents() override;

	virtual bool IsBusy() override;

	//Flying Monster Interface
	virtual bool GetIsFlying() override { return false; }
	virtual class UParticleSystem* GetParticleSystem(int e);

	virtual void SpitFireBall(bool bFireImmediate) override;
private:
	bool bStartedToFall;
};

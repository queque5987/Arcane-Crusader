// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerState.generated.h"

UINTERFACE(MinimalAPI)
class UIPlayerState : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIPlayerState
{
	GENERATED_BODY()

public:
	virtual bool GetState(UINT StateType) { return false; };
	virtual void SetState(UINT StateType, bool b) {};

	virtual bool GetKeyState(UINT StateType) { return false; };
	virtual void SetKeyState(UINT StateType, bool b) {};

	virtual float GetMaxHP() { return 0.f; };
	virtual void SetMaxHP(float NewMaxHP) {};
	virtual float GetMaxStamina() { return 0.f; };
	virtual void SetMaxStamina(float NewMaxStamina) {};

	virtual UINT32 GetPlayerGold() { return 0; };
	virtual void SetPlayerGold(UINT32 e) {};
	virtual void GainPlayerGold(UINT32 e) {};

	virtual void SetRevivalPoint(FVector Pos) {};
	virtual FVector GetRevivalPoint() { return FVector(); };
	virtual void FallToRevivalPoint(class AActor* AttachedCamera, float Damage = 0.f) {};

	virtual void SetHoverringUI(UUserWidget* UI) {};

	virtual void SetStartPos(FVector StartPos) {};

	virtual void Equip(class ACWeapon& ActorToEquip) {};
	virtual void Equip(class AActor& ActorToEquip) {};
	virtual void UnEquip() {};
	virtual void SwitchBruteMode(bool BruteMode) {};

	virtual float GetBonusAttackDamage() { return 0.f; }

	virtual void Heal(float HealPoint) {};

	virtual void StaminaSpend(float RequiredStamina) {};

	virtual void DealtDamage(float AttackDamage, float DamageScale, class ACharacter* TargetCharacter) {};

	virtual void OnHitDown() {};

	virtual FTransform GetSocketTransform(FName SocketName) { return FTransform(); }
	virtual void GetLineTraceResult(FHitResult& HitResult, float AttackRange) {};
	virtual bool GetDealingEnemyTransform(FTransform& OutTransform) { return false; };

	virtual void OnOverlapEnemy(class ACharacter* EnemyChar) {};
	virtual void OnOverlapEndEnemy(class ACharacter* EnemyChar) {};

	virtual void Grasped(class ACharacter& GraspedEnemyCharacter, FName GraspBoneName) {};
	virtual void UnGrasp() {};
//Weapon Effect
	virtual void WeaponEffectActivate() {};
	virtual void WeaponEffectDeactivate() {};
	virtual void SetWeaponEffectCharge(float e, bool IsLeft = false) {};
//Brute Mode
	virtual void BruteRushContinue() {};
	virtual bool IsBruteMode() { return false; };
//Battle Staff Func
	virtual void ThrowStaffEffect() {};
	virtual void TurnBruteMode() {};
	virtual void Ult_ThrowStaffEffectDirect() {};
	virtual void Ult_Jump() {};
	virtual void Ult_PunchInit() {};
	virtual void Ult_Airbone() {};
	virtual void Ult_Land() {};
	virtual void Ult_HitGround() {};
	virtual void Ult_Backflip() {};
//Rifle Staff Func
	virtual void SwitchWeaponHoldingHand(bool ToLeft) {};
	virtual void SpawnAndGraspBeacon() {};
	virtual void ThrowBeacon() {};
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

UINTERFACE(MinimalAPI)
class UIWeapon : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIWeapon
{
	GENERATED_BODY()
public:
	virtual bool GetIsEquiped() { return bool(); }
	virtual void SetIsEquiped(bool e) {};
	virtual void LMB_Attack() {}
	virtual void LMB_Triggered(struct AttackResult& AttackResult) {}
	virtual void LMB_Completed(struct AttackResult& AttackResult) {}
	virtual void RMB_Triggered(struct AttackResult& AttackResult) {}
	virtual void RMB_Completed(struct AttackResult& AttackResult) {}
	virtual void Tab_Triggered(struct AttackResult& AttackResult) {}
	virtual void Ult_Triggered(struct AttackResult& AttackResult) {}
	virtual bool MeleeAttackHitCheck(int32 HitMode = 0, float fDamageScale = 0.f, float _ExplodeRadius = 0.f) { return bool(); };
	virtual void OnAttackSwingEnd() {};
	virtual void SpawnEmitterAttachedToSocket() {};
	virtual void OnEquipped() {};
	virtual void OnUnequipped() {};

	virtual class UStaticMeshComponent* GetStaffStaticMeshComponent() { return nullptr; };

	virtual void SpawnWeaponEffect(int32 Index, FTransform SpawnTransform, float LifeSpan) {};
	virtual void PlaySoundEffect(int32 Index, FVector SpawnLocation, float Volume = 1.f, float Pitch = 1.f) {};
protected:
	virtual class UCInventoryItemData* GetItemData(ACharacter* PC) { return nullptr; };
public:
	virtual void SetAttackDamage(float e) { }
	virtual float GetAttackDamage() { return 0.f; }
	virtual void SetBulletType(int32 e) {}
	virtual void SetItemStat(struct ItemStat* ItemStats) {};
	virtual void SetWeaponName(FName e) { }
	virtual FName GetWeaponName() { return FName(); }
	//BattleStaff Combo1 Projectile Dmage
	virtual float GettempDamage0() { return 0.f; };
	//BattleStaff Combo2 Projectile Dmage 
	virtual float GettempDamage1() { return 0.f; };
	//BattleStaff Combo2 Explode Dmage 
	virtual float GettempDamage2() { return 0.f; };
	virtual float GetRequiredStamina() { return 0.f; }
	virtual void SetRequiredStamina(float e) { }
	virtual class UParticleSystem* GetWeaponEffect(int e) { return nullptr; }
	virtual TArray<class UParticleSystem*>* GetWeaponEffect() {return nullptr; }
	virtual class USoundBase* GetWeaponSoundEffect(int e) { return nullptr; }
	virtual class UStaticMeshSocket* GetSocket(FName e) { return nullptr; }
	virtual class UStaticMeshComponent* GetStaticMeshComponent() { return nullptr; }
	virtual void GetSocketTransform(FTransform& SocketTransform, FName SocketName) {}
	virtual void UpdateCharacterStat() {}

	virtual void ResetDealtEnemies() {};
// Weapon Ora Effect
	virtual void ActivateEffect() {};
	virtual void DeactivateEffect() {};
	virtual void SetCharge(float e, bool IsLeft = false) {};

// Weapon Mode
	virtual int32 GetWeaponMode() { return 0; }

// Battle Only
	virtual void AddBruteGauge(float BG) {};
	virtual float GetBruteGauge() { return 0.f; };
	virtual void GetCurrentHammerEffectLocation(FVector& OutLocation) {};
// Rifle Only
	virtual float GetMaxBullet(int32 BulletType) { return 0.f; }
	virtual float GetCurrBullet(int32 BulletType) { return 0.f; }

	virtual void UltBombArea(FVector BombLocation, float Radius) {};
// Ult Func
	/*BS = ThrowStaffEffect, RS == SpawnAndGraspBeacon*/
	virtual void UltFunc0() {};
	/*BS = TurnBruteMode, RS == ThrowBeacon*/
	virtual void UltFunc1() {};
	/*BS = ThrowStaffEffect Forward*/
	virtual void UltFunc2() {};
	/*BS = Instant Retreive Staff*/
	virtual void UltFunc3() {};
};
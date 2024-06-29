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
	virtual bool MeleeAttackHitCheck() { return bool(); };
	virtual void SpawnEmitterAttachedToSocket() {};
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
};
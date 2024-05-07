// Fill out your copyright notice in the Description page of Project Settings.


#include "IWeapon.h"

/*
* Backup for Weapon.h

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCH.h"
#include "IWeapon.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "CWeapon.generated.h"

UCLASS()
class MMB_API ACWeapon : public AActor, public IIWeapon
{
	GENERATED_BODY()

public:
	ACWeapon(const FObjectInitializer& ObjectInitializer);
	class UStaticMeshComponent* StaticMeshComponent;
	class USphereComponent* Collider;


	bool GetIsEquiped() { return IsEquiped; }
	virtual void SetIsEquiped(bool e);

	virtual void LMB_Attack() {}
	virtual void LMB_Triggered(struct AttackResult& AttackResult) {}
	virtual void LMB_Completed(struct AttackResult& AttackResult) {}
	virtual void RMB_Triggered(struct AttackResult& AttackResult) {}
	virtual void RMB_Completed(struct AttackResult& AttackResult) {}
	virtual bool MeleeAttackHitCheck();
	virtual void SpawnEmitterAttachedToSocket() {};


	TArray<UParticleSystem*> WeaponEffect;
protected:
	float tempDamage0;
	float tempDamage1;
	float tempDamage2;
	float RequiredStamina;

	virtual void BeginPlay() override;

	FName WeaponMesh;

	UPROPERTY(EditAnywhere)
	int32 ItemData_IconTexture;
	UPROPERTY(EditAnywhere)
	int32 ItemData_ItemPrice;
	UPROPERTY(EditAnywhere)
	FString ItemData_AttackType;
	UPROPERTY(EditAnywhere)
	float AttackDamage = 1;
	UPROPERTY(EditAnywhere)
	FName WeaponName;

	bool IsEquiped;
	bool bCasting;
	float CastingClock;
	float DamageScale;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual class UCInventoryItemData* GetItemData(ACharacter* PC);

public:
	virtual void Tick(float DeltaTime) override;

	void SetAttackDamage(float e) { AttackDamage = e; }
	float GetAttackDamage() { return AttackDamage; }
	void SetWeaponName(FName e) { WeaponName = e; }
	FName GetWeaponName() { return WeaponName; }

	//BattleStaff Combo1 Projectile Dmage
	virtual float GettempDamage0() { return 0.f; };
	//BattleStaff Combo2 Projectile Dmage
	virtual float GettempDamage1() { return 0.f; };
	//BattleStaff Combo2 Explode Dmage
	virtual float GettempDamage2() { return 0.f; };
	virtual float GetRequiredStamina() { return RequiredStamina; }
	virtual void SetRequiredStamina(float e) { RequiredStamina = e; }
};

*/
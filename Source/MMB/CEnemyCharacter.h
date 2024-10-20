// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCH.h"
#include "IEnemyStateManager.h"
#include "CEnemyCharacter.generated.h"

DECLARE_DELEGATE(FRoar)
DECLARE_DELEGATE(FAttackHand)
DECLARE_DELEGATE(FAttackHead)
DECLARE_DELEGATE(FAttackFire)
DECLARE_DELEGATE(FAttackMouth)
DECLARE_DELEGATE(FHitReact)

DECLARE_DELEGATE_OneParam(FbAttacking, bool)
UCLASS()
class MMB_API ACEnemyCharacter : public ACharacter, public IIEnemyStateManager
{
	GENERATED_BODY()

public:
	ACEnemyCharacter();

	UFUNCTION()
	void OnOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FRoar DoRoar;
	FAttackHand DoAttackHand;
	FAttackHead DoAttackHead;
	FAttackFire DoAttackFire;
	FAttackMouth DoAttackMouth;
	FHitReact DoHitReact;

	FbAttacking SetBBAttacking;
	UPROPERTY(EditAnyWhere)
	class UDataTable* DropTable;

	//DEPRECATED
	UPROPERTY(EditAnyWhere)
	TArray<FName> DropItemNames;
	//DEPRECATED
	UPROPERTY(EditAnyWhere)
	TArray<float> DropRates;

	UPROPERTY(EditAnyWhere)
	float ArmRadius = 50.f;
	UPROPERTY(EditAnyWhere)
	float HeadRadius = 50.f;
	UPROPERTY(EditAnyWhere)
	float anim = 30.f;

	UPROPERTY(EditAnyWhere)
	float HP = 500;
	UPROPERTY(EditAnyWhere)
	float MaxHP = 500;
protected:
	virtual void BeginPlay() override;

	TArray<UParticleSystem*> EnemyAttackEffect;

	int32 State;

	bool bHostile;
	bool bAttacking;
	bool bAttacking_Comboing;
	float RotationSpeed;
	UPROPERTY(EditAnyWhere)
	float AttackDamage = 20.f;
	float WalkSpeed = 350.f;
	float MaxWalkSpeed = 550.f;
	float MaxWalkSpeedReachSec = 3.f;
	//float DamageScale;
	int AttackPower;
	bool bIsDying = false;
	bool bIsRagdoll = false;

	TArray<FName> BoneNameArr;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual ACharacter* GetDealingPlayer();

	virtual bool IsBusy() override;
	virtual void SetWalkSpeed(float e) override;
	virtual float GetWalkSpeed() override;
	virtual float GetMaxSpeed() override { return MaxWalkSpeed; };
	virtual float GetDefaultSpeed() override { return WalkSpeed; };
	virtual float GetMaxSpeedReachSec() override { return MaxWalkSpeedReachSec; };

	//void SetState(int32 StateType, bool e);
	//bool GetState(int32 StateType);

	void SetbHostile(bool e);
	virtual bool GetHostile() override{ return bHostile; }
	void SetbAttacking(bool e);
	virtual bool GetbAttacking() override { return bAttacking; }
	virtual bool AttackHitCheck(int AttackType = 0, float DamageScale = 0.f) override;
	virtual void HitDamage(float e, ACharacter& Attacker, FVector HitLocation = FVector::ZeroVector);
	float GetHP() { return HP; }
	void SetHP(float e) { HP = e; }
	float GetMaxHP() { return MaxHP; }
	void SetMaxHP(float e) { MaxHP = e; }
	//float GetDamageScale() { return DamageScale; }
	//void SetDamageScale(float e) { DamageScale = e; }
	int GetAttackPower() { return AttackPower; }
	void SetAttackPower(int e) { AttackPower = e; }
	void Die();

	virtual void SetMonsterConfig(struct MonsterConfigure& Config);

	UFUNCTION()
	void OnPlayerDodged();
	UFUNCTION()
	void OnPlayerDodgedEnd();
};

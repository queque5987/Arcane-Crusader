// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCH.h"
#include "CEnemyCharacter.generated.h"

DECLARE_DELEGATE(FRoar)
DECLARE_DELEGATE(FAttackHand)
DECLARE_DELEGATE(FAttackHead)
DECLARE_DELEGATE(FAttackFire)
DECLARE_DELEGATE(FAttackMouth)

DECLARE_DELEGATE_OneParam(FbAttacking, bool)
UCLASS()
class MMB_API ACEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemyCharacter();

	FRoar DoRoar;
	FAttackHand DoAttackHand;
	FAttackHead DoAttackHead;
	FAttackFire DoAttackFire;
	FAttackMouth DoAttackMouth;
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
	float WingClawRadius = 30.f;

	UPROPERTY(EditAnyWhere)
	float HP = 500;
	UPROPERTY(EditAnyWhere)
	float MaxHP = 500;
protected:
	virtual void BeginPlay() override;
	bool bHostile;
	bool bAttacking;
	float RotationSpeed;
	UPROPERTY(EditAnyWhere)
	float AttackDamage = 20.f;
	float WalkSpeed = 350.f;
	float DamageScale;
	int AttackPower;
	bool bIsDying = false;
	bool bIsRagdoll = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetbHostile(bool e);
	bool GetHostile() { return bHostile; }
	void SetbAttacking(bool e);
	bool GetbAttacking() { return bAttacking; }
	bool AttackHitCheck(int AttackType = 0);
	void HitDamage(float e, ACharacter& Attacker, FVector HitLocation = FVector::ZeroVector);
	float GetHP() { return HP; }
	void SetHP(float e) { HP = e; }
	float GetMaxHP() { return MaxHP; }
	void SetMaxHP(float e) { MaxHP = e; }
	float GetDamageScale() { return DamageScale; }
	void SetDamageScale(float e) { DamageScale = e; }
	int GetAttackPower() { return AttackPower; }
	void SetAttackPower(int e) { AttackPower = e; }
	void Die();

	virtual void SetMonsterConfig(struct MonsterConfigure& Config);
};

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
UCLASS()
class MMB_API ACEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACEnemyCharacter();

	FRoar DoRoar;
	FAttackHand DoAttackHand;
	FAttackHead DoAttackHead;
	FAttackFire DoAttackFire;
	UPROPERTY(EditAnyWhere)
	class UDataTable* DropTable;
	UPROPERTY(EditAnyWhere)
	TArray<FName> DropItemNames;
	UPROPERTY(EditAnyWhere)
	TArray<float> DropRates;
	//FDropTableRow 
	//float ArmStretchedOut;
	//UPROPERTY(EditAnyWhere)
	//float ArmStretchedIn;
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bHostile;
	bool bAttacking;
	float RotationSpeed;
	float AttackDamage = 20.f;
	float DamageScale;
	bool bIsDying = false;
	bool bIsRagdoll = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetbHostile(bool e);
	bool GetHostile() { return bHostile; }
	void SetbAttacking(bool e) {
		UE_LOG(LogTemp, Log, TEXT("Set bAttacking to %d"), e);
		bAttacking = e; }
	bool GetbAttacking() { return bAttacking; }
	//void SetbAttackingFree() { bAttacking = false; }
	bool AttackHitCheck(int AttackType = 0);
	void HitDamage(float e, ACharacter& Attacker, FVector HitLocation = FVector::ZeroVector);
	float GetHP() { return HP; }
	void SetHP(float e) { HP = e; }
	float GetMaxHP() { return MaxHP; }
	void SetMaxHP(float e) { MaxHP = e; }
	float GetDamageScale() { return DamageScale; }
	void SetDamageScale(float e) { DamageScale = e; }
	void Die();
};

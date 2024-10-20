// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyCharacter.h"
#include "CEnemy_Barghest.generated.h"

UCLASS()
class MMB_API ACEnemy_Barghest : public ACEnemyCharacter
{
	GENERATED_BODY()
	
	ACEnemy_Barghest();
	class USkeletalMeshComponent* SKManeComponent;
	class USkeletalMeshComponent* SKTailComponent;
	virtual void PostInitializeComponents() override;
public:
	/*Only Do Bite*/
	virtual bool AttackHitCheck(int AttackType = 0, float DamageScale = 0.f) override;
	virtual void HitDamage(float e, ACharacter& Attacker, FVector HitLocation = FVector::ZeroVector) override;
};

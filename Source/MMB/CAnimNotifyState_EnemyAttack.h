// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_EnemyAttack : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	class IIEnemyStateManager* EC;

	/*0 : RHand, 1 : Head, 2 : Mouth, 3 : LHand, 4: Wings, 5: RWing, 6: FireBall Projectile*/
	UPROPERTY(EditAnywhere)
	int AttackType;
	/*Damage Scale of Attack (Total Damage = EnemyCharacter's AttackDamage * DamageScale)*/
	UPROPERTY(EditAnywhere)
	float DamageScale;
	bool ContinueAttack;
};

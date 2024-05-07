// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_EnemyAttack.h"

void UCAnimNotifyState_EnemyAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ContinueAttack = true;
	AttackType = ENEMY_ATTACK_RHAND;
}

void UCAnimNotifyState_EnemyAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (!ContinueAttack) return;
	if (MeshComp)
	{
		if (ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(MeshComp->GetOwner()))
		{
			EC->AttackHitCheck(AttackType) ? ContinueAttack = false : ContinueAttack = true;
		}
	}
}

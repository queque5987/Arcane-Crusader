// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_EnemyAttackCheck.h"

UCAnimNotify_EnemyAttackCheck::UCAnimNotify_EnemyAttackCheck()
{
	AttackType = ENEMY_ATTACK_RHAND;
}

void UCAnimNotify_EnemyAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		if (ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(MeshComp->GetOwner()))
		{
			EC->AttackHitCheck(AttackType);
		}
	}
}

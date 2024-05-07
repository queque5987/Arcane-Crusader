// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_EnemyAtk_Wing.h"

void UCAnimNotifyState_EnemyAtk_Wing::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ContinueAttack = true;
	AttackType = ENEMY_ATTACK_WINGS;
}

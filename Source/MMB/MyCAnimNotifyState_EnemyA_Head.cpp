// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCAnimNotifyState_EnemyA_Head.h"

void UMyCAnimNotifyState_EnemyA_Head::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	AttackType = ENEMY_ATTACK_HEAD;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_AttackCancleUnLock.h"

void UCAnimNotify_AttackCancleUnLock::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner()))
	{
		PC->SetState(PLAYER_ATTACK_CANCLE_UNLOCK, true);
	}
}

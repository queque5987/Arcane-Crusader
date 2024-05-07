// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_AttackCancleLock.h"

void UCAnimNotify_AttackCancleLock::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner()))
	{
		PC->SetState(PLAYER_ATTACK_CANCLE_UNLOCK, false);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerRollInvin.h"

void UCAnimNotifyState_PlayerRollInvin::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPlayerCharacter(MeshComp))
	{
		PC->SetState(PLAYER_ROLL_INVINCIBLE, true);
	}
}

void UCAnimNotifyState_PlayerRollInvin::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (PC != nullptr)
	{
		PC->SetState(PLAYER_ROLL_INVINCIBLE, false);
	}
}

bool UCAnimNotifyState_PlayerRollInvin::GetPlayerCharacter(USkeletalMeshComponent* MeshComp)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	return (PC != nullptr) ? true : false;
}

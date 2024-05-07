// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerComboWait.h"

void UCAnimNotifyState_PlayerComboWait::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPC(MeshComp))
	{
		PC->SetContinueCombo(false);
		PC->SetState(PLAYER_ATTACK_CANCLE_UNLOCK, false);
	}
}

void UCAnimNotifyState_PlayerComboWait::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (GetPC(MeshComp))
	{
		if (!PC->GetContinueCombo())
		{
			PC->StopAnimMontage();
			PC->SetState(PLAYER_ATTACKING, false);
		}
	}
}

void UCAnimNotifyState_PlayerComboWait::ResetComboStack()
{
	if (PC == nullptr) return;
	PC->SetState(PLAYER_COMBO_STACK_1, false);
	PC->SetState(PLAYER_COMBO_STACK_2, false);
	PC->SetState(PLAYER_COMBO_STACK_3, false);
}

bool UCAnimNotifyState_PlayerComboWait::GetPC(USkeletalMeshComponent* MeshComp)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	return (PC!=nullptr)? true : false;
}
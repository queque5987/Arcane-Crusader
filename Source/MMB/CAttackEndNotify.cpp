// Fill out your copyright notice in the Description page of Project Settings.


#include "CAttackEndNotify.h"

void UCAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (PC != nullptr)
	{
		PC->SetState(PLAYER_ATTACKING, false);
		PC->SetState(PLAYER_COMBO_STACK_1, false);
		PC->SetState(PLAYER_COMBO_STACK_2, false);
		PC->SetState(PLAYER_COMBO_STACK_3, false);
		PC->SetState(PLAYER_ATTACK_CANCLE_UNLOCK, false);
		//PC->SetIsAttacking(false);
	}
	//UE_LOG(LogTemp, Log, TEXT("Notify Mesh Comp Owner Nanme: %s"), *MeshComp->GetOwner()->GetClass()->GetName());
}

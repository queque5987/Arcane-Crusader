// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_PlayerDownRecoverEnd.h"

void UCAnimNotify_PlayerDownRecoverEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner()))
		{
			PC->SetState(PLAYER_GETTINGUP, false);
		}
	}
}

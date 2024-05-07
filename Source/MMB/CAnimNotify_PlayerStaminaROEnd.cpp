// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_PlayerStaminaROEnd.h"

void UCAnimNotify_PlayerStaminaROEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner()))
		{
			PC->SetState(PLAYER_STAMINA_RUNOUT, false);
		}
	}
}

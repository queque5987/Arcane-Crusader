// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_PlayerHitRegdoll.h"


void UCAnimNotify_PlayerHitRegdoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner()))
		{
			PC->OnHitDown();
		}
	}
}

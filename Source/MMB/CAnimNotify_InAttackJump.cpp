// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_InAttackJump.h"

void UCAnimNotify_InAttackJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (MeshComp)
	{
		if (ACharacter* PC = Cast<ACharacter>(MeshComp->GetOwner()))
		{
			PC->Jump();
		}
	}
}

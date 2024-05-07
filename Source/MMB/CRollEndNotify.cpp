// Fill out your copyright notice in the Description page of Project Settings.


#include "CRollEndNotify.h"

void UCRollEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (PC != nullptr) PC->SetState(PLAYER_ROLLING, false);
}

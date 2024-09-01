// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerBruteRush.h"
#include "IPlayerState.h"
#include "PCH.h"

void UCAnimNotifyState_PlayerBruteRush::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
}

void UCAnimNotifyState_PlayerBruteRush::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;
	PlayerState->BruteRushContinue();
}

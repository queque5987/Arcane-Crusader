// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerBStep.h"

void UCAnimNotifyState_PlayerBStep::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	ScaleValue *= -1.f;
}

void UCAnimNotifyState_PlayerBStep::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (PC != nullptr)
	{
		FVector Curr = PC->GetActorLocation();
		PC->SetActorLocation(Curr + Direction * ScaleValue);
	}
}

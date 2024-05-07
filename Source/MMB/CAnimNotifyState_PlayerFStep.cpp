// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerFStep.h"

void UCAnimNotifyState_PlayerFStep::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	ScaleValue = 20.f;
	if (PC != nullptr) Direction = PC->GetActorForwardVector();
}

void UCAnimNotifyState_PlayerFStep::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (PC != nullptr)
	{
		PC->AddMovementInput(Direction, ScaleValue, true);
		/*FVector Curr = PC->GetActorLocation();
		PC->SetActorLocation(Curr + Direction * ScaleValue);*/
	}
}

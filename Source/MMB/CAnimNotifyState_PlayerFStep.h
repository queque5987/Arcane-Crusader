// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PCH.h"
#include "CAnimNotifyState_PlayerFStep.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_PlayerFStep : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
protected:
	ACPlayerCharacter* PC;
	float ScaleValue;
	FVector Direction;
};

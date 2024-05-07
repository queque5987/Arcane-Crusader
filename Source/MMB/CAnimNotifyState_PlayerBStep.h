// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_PlayerFStep.h"
#include "CAnimNotifyState_PlayerBStep.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_PlayerBStep : public UCAnimNotifyState_PlayerFStep
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PCH.h"
#include "CAnimNotifyState_PlayerRollInvin.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_PlayerRollInvin : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
protected:
	ACPlayerCharacter* PC;
	bool GetPlayerCharacter(USkeletalMeshComponent* MeshComp);
};

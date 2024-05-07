// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CPlayerCharacter.h"
#include "CAnimNotifyState_PlayerAttack.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_PlayerAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
protected:
	bool StopAttack;
	ACPlayerCharacter* PC;
	bool GetPlayerCharacter(USkeletalMeshComponent* MeshComp);
};

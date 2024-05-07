// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CEnemyCharacter.h"
#include "CAnimNotifyState_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_EnemyAttack : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	int AttackType;
	bool ContinueAttack;
};

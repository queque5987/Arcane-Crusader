// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_EnemyAttack.h"
#include "CAnimNotifyState_EnemyAtk_FlyF.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_EnemyAtk_FlyF : public UCAnimNotifyState_EnemyAttack
{
	GENERATED_BODY()
private:
	FRotator TargetRot;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	
	float RotationAcc;
	float MaxRotAcc = 0.8f;
};

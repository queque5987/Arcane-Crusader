// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_EnemyAttack.h"
#include "MyCAnimNotifyState_EnemyA_Head.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UMyCAnimNotifyState_EnemyA_Head : public UCAnimNotifyState_EnemyAttack
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};

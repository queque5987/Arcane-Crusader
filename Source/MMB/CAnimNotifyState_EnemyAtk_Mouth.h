// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_EnemyAttack.h"
#include "CAnimNotifyState_EnemyAtk_Mouth.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_EnemyAtk_Mouth : public UCAnimNotifyState_EnemyAttack
{
	GENERATED_BODY()
private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};

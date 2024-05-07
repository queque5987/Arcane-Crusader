// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotify_AttackCancleUnLock.h"
#include "CAnimNotify_AttackCancleLock.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotify_AttackCancleLock : public UCAnimNotify_AttackCancleUnLock
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

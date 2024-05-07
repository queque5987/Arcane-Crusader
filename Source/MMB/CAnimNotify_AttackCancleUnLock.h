// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PCH.h"
#include "CAnimNotify_AttackCancleUnLock.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotify_AttackCancleUnLock : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAttackEndNotify.h"
#include "CRollEndNotify.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCRollEndNotify : public UCAttackEndNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

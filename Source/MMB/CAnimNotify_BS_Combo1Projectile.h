// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotify_SpawnEmitter.h"
#include "CAnimNotify_BS_Combo1Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotify_BS_Combo1Projectile : public UCAnimNotify_SpawnEmitter
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

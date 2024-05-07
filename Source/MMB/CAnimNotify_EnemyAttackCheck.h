// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CEnemyCharacter.h"
#include "CAnimNotify_EnemyAttackCheck.generated.h"

UCLASS()
class MMB_API UCAnimNotify_EnemyAttackCheck : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UCAnimNotify_EnemyAttackCheck();
	int AttackType;
};

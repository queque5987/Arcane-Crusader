// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyAnimInstance.h"
#include "CEnemy_AnimInstance_Nightmare.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCEnemy_AnimInstance_Nightmare : public UCEnemyAnimInstance
{
	GENERATED_BODY()

	UCEnemy_AnimInstance_Nightmare();
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void Roar() override;
	virtual void AttackHand() override;
	virtual void AttackHead() override;
};

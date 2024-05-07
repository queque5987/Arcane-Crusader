// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBTTaskAttack.h"
#include "CBTTaskAttackHead.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTTaskAttackHead : public UCBTTaskAttack
{
	GENERATED_BODY()

protected:
	virtual void DoAttack(ACEnemyCharacter* EC) override;
};

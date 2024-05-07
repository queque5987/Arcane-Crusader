// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBTTaskAttack.h"
#include "CBTTaskAttack_Fire.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTTaskAttack_Fire : public UCBTTaskAttack
{
	GENERATED_BODY()
	virtual void DoAttack(ACEnemyCharacter* EC) override;
};

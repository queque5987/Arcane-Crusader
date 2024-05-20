// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBTTaskAttack.h"
#include "CBTTaskAttack_Mouth.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTTaskAttack_Mouth : public UCBTTaskAttack
{
	GENERATED_BODY()
protected:
	virtual void DoAttack(class ACEnemyCharacter* EC);
	
};

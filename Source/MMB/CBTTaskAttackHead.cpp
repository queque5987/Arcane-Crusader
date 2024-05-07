// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskAttackHead.h"

void UCBTTaskAttackHead::DoAttack(ACEnemyCharacter* EC)
{
	EC->DoAttackHead.ExecuteIfBound();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskAttack_Fire.h"
#include "CEnemyCharacter.h"

void UCBTTaskAttack_Fire::DoAttack(ACEnemyCharacter* EC)
{
	EC->DoAttackFire.ExecuteIfBound();
}

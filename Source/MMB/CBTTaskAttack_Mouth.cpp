// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskAttack_Mouth.h"
#include "CEnemyCharacter.h"

void UCBTTaskAttack_Mouth::DoAttack(ACEnemyCharacter* EC)
{
	EC->DoAttackMouth.ExecuteIfBound();
}

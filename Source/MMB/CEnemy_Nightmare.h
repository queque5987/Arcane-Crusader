// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyCharacter.h"
#include "CEnemy_Nightmare.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API ACEnemy_Nightmare : public ACEnemyCharacter
{
	GENERATED_BODY()
	
	ACEnemy_Nightmare();

	virtual void PostInitializeComponents() override;
};

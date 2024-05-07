// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBTTaskFindPatrolPosFly.h"
#include "CBTTaskFindPatrolPosFlyAtk.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCBTTaskFindPatrolPosFlyAtk : public UCBTTaskFindPatrolPosFly
{
	GENERATED_BODY()
	UCBTTaskFindPatrolPosFlyAtk();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

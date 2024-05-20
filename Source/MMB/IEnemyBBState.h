// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyBBState.generated.h"

UINTERFACE(MinimalAPI)
class UIEnemyBBState : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIEnemyBBState
{
	GENERATED_BODY()

public:
	virtual bool GetbSeePlayer() { return false; }
	virtual void SetbBusy(bool e) {}
	virtual bool GetbBusy() { return false; }
	virtual FVector GetPlayerPos() { return FVector::ZeroVector; }
	virtual void SetRNG(float e) {}
	virtual void SetTargetDetected(ACharacter* actor) {}
};

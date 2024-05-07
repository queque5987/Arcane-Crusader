// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IFlyMonster_AIController.generated.h"

UINTERFACE(MinimalAPI)
class UIFlyMonster_AIController : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIFlyMonster_AIController
{
	GENERATED_BODY()

public:
	virtual FVector GetFlyPatrolPos() { return FVector(); }
};

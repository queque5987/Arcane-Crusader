// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerState.generated.h"

UINTERFACE(MinimalAPI)
class UIPlayerState : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIPlayerState
{
	GENERATED_BODY()

public:
	virtual bool GetState(UINT StateType) { return false; };
	virtual void SetState(UINT StateType, bool b) {};
	virtual void SetRevivalPoint(FVector Pos) {};
};
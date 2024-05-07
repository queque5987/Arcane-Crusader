// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEntrance.generated.h"

UINTERFACE(MinimalAPI)
class UIEntrance : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIEntrance
{
	GENERATED_BODY()

public:

	virtual void SetOpenGate(bool e) {}
	virtual bool GetOpenGate() { return false; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWidgetInteract.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIWidgetInteract : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIWidgetInteract
{
	GENERATED_BODY()

public:

	virtual void OnRightClicked() {};
	virtual void SwitchPressed(bool Pressed) {};
	virtual bool GetbPressed() { return false; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerQuest.generated.h"

UINTERFACE(MinimalAPI)
class UIPlayerQuest : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIPlayerQuest
{
	GENERATED_BODY()

public:
	virtual void QuestClear(int e) {};
	virtual void QuestInitialize(int e) {};
};

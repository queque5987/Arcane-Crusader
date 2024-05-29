// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSaveFileUI.h"
#include "CSaveFileSelectUI.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCSaveFileSelectUI : public UCSaveFileUI
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	//UFUNCTION()
	virtual void OnButtonClicked() override;
};

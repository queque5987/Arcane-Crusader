// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CStaticNPC.h"
#include "CEthereal.generated.h"
UCLASS()
class MMB_API ACEthereal : public ACStaticNPC
{
	GENERATED_BODY()
	
	ACEthereal();

protected:
	virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere)
	//TArray<FName> PossessItems;
public:
	virtual void Initialize() override;
};

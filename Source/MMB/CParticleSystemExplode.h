// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "CParticleSystemExplode.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCParticleSystemExplode : public UParticleSystemComponent
{
	GENERATED_BODY()
	UCParticleSystemExplode();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float tempfloat = 0.f;
//public:
//	virtual void FinishDestroy() override;
};

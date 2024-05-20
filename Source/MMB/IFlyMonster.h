// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IFlyMonster.generated.h"

UINTERFACE(MinimalAPI)
class UIFlyMonster : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIFlyMonster
{
	GENERATED_BODY()
public:
	virtual float GetCurrentAltitude() { return 0.f; }
	virtual float GetFlyMovementSpeed() { return 0.f; }
	virtual float GetMaxAltitude() { return 0.f; }
	virtual void SetIsFlying(bool e) {}
	virtual bool GetIsFlying() { return false; }
	virtual float GetRotationSpeed() { return 0.f; }
	virtual bool FlyTo(FVector Destination, float DeltaSeconds, float AcceptableRadius, float AccWeight = 1.f) { return false; }
	virtual bool FlyTo(FRotator DestinedRotation, float DeltaSeconds, float AccWeight = 1.f) { return false; }
	virtual bool RotateTo(FVector Destination, float DeltaSeconds, float AccWeight = 1.f) { return false; }

	virtual class UParticleSystem* GetParticleSystem(int e) { return nullptr; }
};
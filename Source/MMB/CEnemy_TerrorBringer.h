// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyCharacter.h"
#include "IFlyMonster.h"
#include "CEnemy_TerrorBringer.generated.h"

DECLARE_DELEGATE(FFlyFire);
UCLASS()
class MMB_API ACEnemy_TerrorBringer : public ACEnemyCharacter, public IIFlyMonster
{
	GENERATED_BODY()
	
	ACEnemy_TerrorBringer();
private:
	bool IsFlying;
	float MaxAltitude;
	float CurrentAltitude;
	float VirtialAcc;
	float FlyAcc;

	TArray<UParticleSystem*> EnemyAttackEffect;
public:
	FFlyFire DoFlyFireAttack;

	UPROPERTY(EditAnywhere)
	float projscale;
	UPROPERTY(EditAnywhere)
	//FVector FireLocation;
	float projspeed;
	UPROPERTY(EditAnywhere)
	float projclock;
	UPROPERTY(EditAnywhere)
	float projscaleA;
	UPROPERTY(EditAnywhere)
	FRotator projR;
	//FVector FireScale;

	virtual void Tick(float DeltaTime) override;

	virtual float GetCurrentAltitude() override { return CurrentAltitude; }
	virtual float GetFlyMovementSpeed() override;
	virtual float GetMaxAltitude() override { return MaxAltitude; }
	virtual void SetIsFlying(bool e) override;
	virtual bool GetIsFlying() override { return IsFlying; }
	virtual float GetRotationSpeed() override { return RotationSpeed; }
	virtual bool FlyTo(FVector Destination, float DeltaSeconds, float AcceptableRadius) override;
	virtual bool FlyTo(FRotator DestinedRotation, float DeltaSeconds, float AccWeight) override;

	virtual class UParticleSystem* GetParticleSystem(int e) override;
};

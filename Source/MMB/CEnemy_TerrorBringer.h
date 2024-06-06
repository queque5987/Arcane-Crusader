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
	virtual void PostInitializeComponents() override;
private:
	bool IsFlying;

	float MaxAltitude = 200.f;
	float CurrentAltitude = 0.f;
	float VirtialAcc = 120.f;
	float FlyAcc = 0.5f;

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
	virtual bool FlyTo(FVector Destination, float DeltaSeconds, float AcceptableRadius, float AccWeight = 1.f) override;
	virtual bool FlyTo(FRotator DestinedRotation, float DeltaSeconds, float AccWeight) override;
	virtual bool RotateTo(FVector Destination, float DeltaSeconds, float AccWeight = 1.f) override;

	virtual class UParticleSystem* GetParticleSystem(int e) override;
	virtual void SetMonsterConfig(struct MonsterConfigure& Config) override;
};

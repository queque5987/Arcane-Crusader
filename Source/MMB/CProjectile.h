// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "CParticleSystemExplode.h"
#include "PCH.h"
#include "CProjectile.generated.h"

UCLASS()
class MMB_API ACProjectile : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ACProjectile();
	class USphereComponent* Collider;
	class UStaticMeshComponent* StaticMeshComponent;
	class UParticleSystemComponent* ParticleSystemFireBall;
	class UParticleSystemComponent* ParticleSystemExplode;
	class UParticleSystemComponent* ParticleSystemSpawnEffect;
	class UParticleSystemComponent* ParticleSystemLaunchEffect;
	class APawn* OwnerPawn;
	class ACharacter* PC;
	UFUNCTION()
	void OnExplodeFinished(class UParticleSystemComponent* ParticleSystem);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void Explode(bool Hit);

	ACharacter* SweepActor;
	FVector HitLocation;
	float PenetrationTick = 0.4f;
	int PenetrationTickCounter;

	bool Launch;
	float Trail;
	float ElipsedTime;
	float LimitTime;
	float Acceleration;
	float TotalDamage;
	bool bPenetrate;
	bool bOnlyDestructOnClock;

	//Configure//
	float AccCoefficient;
	float MaxSpeedCoefficient;
	//Configure//

	FTimerHandle LaunchTimerHandle;
	bool bSnowball = false;
	float fSnowball = 0.01f;

	int PlayerReactPower = 0;

	USoundBase* ExplodeSE;
	USoundBase* LaunchSE;
private:
	void SweepOnLaunch();
public:	
	virtual void Tick(float DeltaTime) override;
	void SetLaunch(UParticleSystem* ProjectileEffect, UParticleSystem* ExplodeEffect, float RangeLimit = 1500.f, float Acc = 20.f, float LaunchClock = 0.f, float ClockLimit = -1.f, bool Snowball = false, float SnowballAcc = 0.01f);
	void SetLaunch(ACharacter* PC,
		UParticleSystem* ProjectileEffect, UParticleSystem* ExplodeEffect, UParticleSystem* SpawnEffect, UParticleSystem* LaunchEffect,
		float Damage, float RangeLimit = 1500.f, float Acc = 20.f, float ClockLimit = -1.f,
		struct DELAY_START_PROJECTILE_CONFIGURE* config = nullptr,
		bool DoPenetrate = false, bool OnlyDestructOnClock = false, bool Snowball = false, float SnowballAcc = 0.01f,
		USoundBase* pExplodeSE = nullptr, USoundBase* pLaunchSE = nullptr
	);
	void SetPlayerReactPower(int e) { PlayerReactPower = e; }
	UFUNCTION()
	void SetLaunchQuick();
	void SetProjCollisionScale(float e);

	void SetExplodeSE(USoundBase* SE) { ExplodeSE = SE; }
	void SetLaunchSE(USoundBase* SE) { LaunchSE = SE; }

	void SetProjectileScae(FVector e);
};

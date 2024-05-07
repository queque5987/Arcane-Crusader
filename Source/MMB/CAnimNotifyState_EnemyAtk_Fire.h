// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_EnemyAttack.h"
#include "Particles/ParticleSystem.h"
#include "Containers/Queue.h"
#include "CAnimNotifyState_EnemyAtk_Fire.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_EnemyAtk_Fire : public UCAnimNotifyState_EnemyAttack
{
	GENERATED_BODY()

protected:
	UParticleSystem* FireEffect;
	FTimerHandle AttackTimerHandle;
	TQueue<class UParticleSystemComponent*> FEQueue;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
public:
	UFUNCTION()
	void FEOff();

	//FName, EventName, float, EmitterTime, int32, ParticleTime, FVector, Location, FVector, Velocity, FVector, Direction, FVector, Normal, FName, BoneName, UPhysicalMaterial*, PhysMat
	//UFUNCTION()
	//void ParticleCollideTest(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat);
};

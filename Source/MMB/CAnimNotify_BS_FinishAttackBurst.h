// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAnimNotify_SpawnEmitter.h"
#include "Containers/Queue.h"
#include "CAnimNotify_BS_FinishAttackBurst.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotify_BS_FinishAttackBurst : public UCAnimNotify_SpawnEmitter
{
	GENERATED_BODY()
	UCAnimNotify_BS_FinishAttackBurst();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	TArray<FTimerHandle> ArrExplodeTimerHandler;
	TQueue<FVector> SpawnLocations;
	float ExplodeRadius = 120.f;

	void SpawnBonusExplosion(FVector SpawnLocation, FRotator ActorRotation, float DelayClock);
	bool Sweep(FHitResult& HitResult, FVector SpawnLocation);
	void test();
};
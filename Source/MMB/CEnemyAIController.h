// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "PCH.h"
#include "IEnemyBBState.h"
#include "IEnemyAITactics.h"
#include "CEnemyAIController.generated.h"

UCLASS()
class MMB_API ACEnemyAIController : public AAIController, public IIEnemyBBState, public IIEnemyAITactics
{
	GENERATED_BODY()
	
	//ACEnemyAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	ACEnemyAIController(const FObjectInitializer& ObjectInitializer);
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);

	UFUNCTION()
	void SetPerceptionSystem();

	UFUNCTION()
	void SetbBusyFree(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void SetbBusyUnFree(UAnimMontage* Montage);

	virtual void Tick(float DeltaTime) override;

	class UAISenseConfig_Sight* SightConfig;
protected:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
	ACharacter* ChasingPlayer;
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName bSeePlayer;
	static const FName PlayerPos;
	static const FName bHostile;
	static const FName bBusy;
	static const FName bAttacking;
	static const FName PlayerCharacter;
	static const FName CornAheadPos;

	FTimerHandle RoarTimerHandle;
	void RoarCooldownTimer() { CanRoar = true; }

	//void SetPerceptionComponent(UAIPerceptionComponent& InPerceptionComponent);
	ACharacter* GetChasingPlayer() { return ChasingPlayer; }
	FVector GetChasingPlayerPos();
	virtual void SetbBusy(bool e) override;
	virtual bool GetbBusy() override;
	void SetbAttacking(bool e);
	bool GetbAttacking();
	bool GetCanRoar() { return CanRoar; }
	void SetCanRoar(bool e) { CanRoar = e; }
	float GetRoarCooldown() { return RoarCooldown; }
	void SetRoarCooldown(float e) { RoarCooldown = e; }
	void SetRoarCooldownTimer();


	virtual bool GetbSeePlayer() override;
	virtual void SetRNG(float e) override;
	virtual FVector GetPlayerPos() override;
	virtual void SetTargetDetected(ACharacter* actor) override;
	virtual void SetIsStrafe(float e) override;
protected:
	void OnPlayerLoseTimer();
	bool CanRoar : true;

	FTimerHandle PlayerLoseTimerHandle;
	float PlayerLoseInterval;
	float RoarCooldown;

// AI Tactics
public:
	virtual ACharacter* GetPlayer() override;
	virtual bool IsPlayerAttacking() override;
	virtual float GetPlayerDistance() override;
	virtual FVector GetPlayerVelocity() override;
	virtual FVector GetPlayerLocation() override;
};

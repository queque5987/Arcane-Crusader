// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "PCH.h"
#include "CEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API ACEnemyAIController : public AAIController
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
	static const FName PlayerCharacter;

	FTimerHandle RoarTimerHandle;
	void RoarCooldownTimer() { CanRoar = true; }

	//void SetPerceptionComponent(UAIPerceptionComponent& InPerceptionComponent);
	ACharacter* GetChasingPlayer() { return ChasingPlayer; }
	FVector GetChasingPlayerPos();
	void SetbBusy(bool e);
	bool GetbBusy();
	bool GetCanRoar() { return CanRoar; }
	void SetCanRoar(bool e) { CanRoar = e; }
	float GetRoarCooldown() { return RoarCooldown; }
	void SetRoarCooldown(float e) { RoarCooldown = e; }
	void SetRoarCooldownTimer();

protected:
	void OnPlayerLoseTimer();
	bool CanRoar : true;

	FTimerHandle PlayerLoseTimerHandle;
	float PlayerLoseInterval;
	float RoarCooldown;
};

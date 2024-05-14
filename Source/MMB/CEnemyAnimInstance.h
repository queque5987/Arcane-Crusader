// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UCEnemyAnimInstance();
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);
protected:
	UPROPERTY(BlueprintReadOnly)
	APawn* Pawn;
	UPROPERTY(BlueprintReadOnly)
	class ACEnemyAIController* PawnController;
	UPROPERTY(BlueprintReadOnly)
	bool IsAir;
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(BlueprintReadOnly)
	float ZSpeed;
	UPROPERTY(BlueprintReadOnly)
	float PawnAnimRadian;
	UPROPERTY(BlueprintReadOnly)
	bool IsHostile;

	UAnimSequenceBase* AnimSequenceRoar;
	UAnimSequenceBase* AnimSequenceAttackHand;
	UAnimSequenceBase* AnimSequenceAttackHead;
	//UAnimSequenceBase* AnimSequenceRMBCastOngoing;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateProperties(float Delta);

	class ACEnemyCharacter* EnemyCharacter;
public:
	UFUNCTION()
	virtual void Roar();
	UFUNCTION()
	virtual void AttackHand();
	UFUNCTION()
	virtual void AttackHead();

	void SetIsHostile(bool e) { IsHostile = e; }
	bool GetIsHostile() { return IsHostile; }

	UFUNCTION()
	void SetbAttackingFree(UAnimMontage* Montage, bool bInterrupted);
};
